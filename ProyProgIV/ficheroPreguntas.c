/*
 * ficheroTexto.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */
#include "ficheroPreguntas.h"

#include "pregunta.h"
#include <stdio.h>
#include <stdlib.h>

#define NOMBRE_FIC "ficheroPreguntas.txt"

//Array de almacenamiento
Pregunta *preguntas;

int numPreguntas = 0;
int numeroMax = 0;

/**
 * Busca una pregunta concreta en el fichero de texto y la devuelve
 *
 * @param char* que contiene el codigo de la pregunta que se quiere buscar
 * @return pregunta leida de fichero correpondiete a ese codigo
 */
Pregunta buscarPreguntaEnFichero(char *codigo) {

	int posEncontrado = buscarPosPregunta(codigo);
	return preguntas[posEncontrado];
}
/**
 * Busca la posicion de en la array de la pregunta segun el codigo pasado como parametro
 * @param codigo de la pregunta
 * @return posicion de la pregunta en la array, -1 si no encontrado
 */
int buscarPosPregunta(char *codigo) {
	int posEncontrado = -1;
	for (int i = 0; i < numPreguntas; i++) {
		if (strcmp(generarCodigo(preguntas[i]), codigo) == 0) {
			posEncontrado = i;
			break;
		}
	}
	return posEncontrado;
}

/**
 * Inserta una pregunta en el fichero de texto
 * @param pregunta a escribir
 */
void insertarPregunta(Pregunta p) {
	//Mientras no se supere el maximo
	if (numPreguntas < numeroMax) {

		preguntas[numPreguntas] = p;

		numPreguntas++;
	} else { //Si se supera el maximo es necesario reservar mas sitio

		numeroMax += 10;
		Pregunta *preguntasRealloc = realloc(preguntas,
				sizeof(Pregunta) * numeroMax); //Reserva para para 10 preguntas mas que antes

		preguntas = preguntasRealloc;

		insertarPregunta(p); //La pregunta ya se puede almacenar
	}
}
/**
 * Borra una pregunta del fichero de texto
 * @param codigo que representa a la pregunta a borrar
 */
void borrarPregunta(char *codigo) {

	int posEncontrado = buscarPosPregunta(codigo);
	//Eliminar y mover hacia la izquierda
	for (int i = posEncontrado; i < numPreguntas - 1; i++) {
		preguntas[i] = preguntas[i + 1];
	}
	numPreguntas--;
}
/**
 * Imprime todas las perguntas almacenadas, una detras de otra
 */
void printTodasPreguntas() {
	for (int i = 0; i < numPreguntas; i++) {
		printPregunta(&preguntas[i]);
		printf("\n");
	}
}
/**
 * Carga las preguntas del fichero y las guarda en la array
 */
void cargarPreguntas() {

	FILE *fr = fopen(NOMBRE_FIC, "r");

	fscanf(fr, "%i\n", &numeroMax); //Lee el numero de preguntas y lo asume como maximo

	preguntas = malloc(sizeof(Pregunta) * numeroMax); //reserva espacio para el numero de preguntas indicado

	//Para cada pregunta
	for (int i = 0; i < numeroMax; i++) {
		//Reserva de espacio para todos los strings
		char *cod = malloc(sizeof(char) * (11 + 1)); //el codigo son 11 caracteres mas el \0
		char *preg = malloc(sizeof(char) * NUM_C_STR);
		char *ops1 = malloc(sizeof(char) * NUM_C_STR);
		char *ops2 = malloc(sizeof(char) * NUM_C_STR);
		char *ops3 = malloc(sizeof(char) * NUM_C_STR);
		char *ops4 = malloc(sizeof(char) * NUM_C_STR);
		char *res = malloc(sizeof(char));

		//Lee la linea del fichero de texto segun el formato y almacena lo leido en los punteros indicados
		fscanf(fr, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",
				cod, preg, ops1, ops2, ops3, ops4, res);

		//Sacar la categoria de el codigo de la pregunta
		char *cat = malloc(sizeof(char) * (2 + 1)); //La categoria son 2 caracteres y el \0
		cat[0] = cod[0];
		cat[1] = cod[1];
		cat[2] = '\0';

		//Crea la lista de "strings" con la informacion de la preguunta
		char *lista[] = { cat, preg, ops1, ops2, ops3, ops4, res };

		insertarPregunta(crearPregunta(lista)); //Crea la pregunta y la inserta

		//Libera los punteros que se pueden liberar (no se debe liberar preg)
		free(cod);
		free(ops1);
		free(ops2);
		free(ops3);
		free(ops4);
		free(res);

	}

	fclose(fr);
}
/**
 * Almacena las preguntas de la array en un fichero de texto
 */
void guardarPreguntas() {

	FILE *fw = fopen(NOMBRE_FIC, "w");

	fprintf(fw, "%i\n", numPreguntas); //Guarda el numero de preguntas

	//Por cada pregunta
	for (int i = 0; i < numPreguntas; i++) {
		//Guarda el string con la información de la pregunta
		char *strPreg = preguntaParaFichero(preguntas[i]);
		fprintf(fw, "%s\n", strPreg);
		free(strPreg);
	}

	fclose(fw);
}
/**
 * Formatea la pregunta a una linea de texto preparada para el fichero de texto
 *
 * @param Pregunta que se quiere formatear
 * @return string con el formato requerido para la escritura en el fichero
 */
char* preguntaParaFichero(Pregunta p) {
	int longStr = NUM_C_STR * 6;
	char *str = malloc(sizeof(char) * longStr);
	sprintf(str, "%s\t%s\t%s\t%s\t%s\t%s\t%i", generarCodigo(p), p.preg,
			p.ops[0], p.ops[1], p.ops[2], p.ops[3], p.res);
	return str;
}

