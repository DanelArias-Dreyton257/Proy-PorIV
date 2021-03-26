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

//Array provisional para la preparacion de funciones
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
	//TODO hacer la busqueda real
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
	if (numPreguntas < numeroMax) {

		preguntas[numPreguntas] = p;

		numPreguntas++;
	} else {
		numeroMax += 10;
		Pregunta *preguntasRealloc = realloc(preguntas,
				sizeof(Pregunta) * numeroMax);

		preguntas = preguntasRealloc;

		insertarPregunta(p);
	}
}
/**
 * Borra una pregunta del fichero de texto
 * @param codigo que representa a la pregunta a borrar
 */
void borrarPregunta(char *codigo) {
	//PROVISIONAL CAMBIAR MAS ADELANTE TODO
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

void cargarPreguntas() {

	FILE *fr = fopen(NOMBRE_FIC, "r");

	fscanf(fr, "%i\n", &numeroMax);

	preguntas = malloc(sizeof(Pregunta)*numeroMax);

	for (int i = 0; i < numeroMax; i++) {
		char *cod = malloc(sizeof(char) * 15);
		char *preg = malloc(sizeof(char) * 100);
		char *ops1 = malloc(sizeof(char) * 100);
		char *ops2 = malloc(sizeof(char) * 100);
		char *ops3 = malloc(sizeof(char) * 100);
		char *ops4 = malloc(sizeof(char) * 100);
		char *res = malloc(sizeof(char));

		//SUPER FIXME
		fscanf(fr, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", cod, preg, ops1, ops2, ops3,
				ops4, res);

		char *cat = malloc(sizeof(char) * (2 + 1));
		cat[0] = cod[0];
		cat[1] = cod[1];
		cat[2] = '\0';

		char *lista[] = { cat, preg, ops1, ops2, ops3, ops4, res };

		insertarPregunta(crearPregunta(lista));

		free(cod);
		free(preg);
		free(ops1);
		free(ops2);
		free(ops3);
		free(ops4);
		free(res);
		free(cat);

	}

	fclose(fr);
}

void guardarPreguntas() {

	FILE *fw = fopen(NOMBRE_FIC, "w");

	fprintf(fw, "%i\n", numPreguntas);

	for (int i = 0; i < numPreguntas; i++) {
		char *strPreg = preguntaParaFichero(preguntas[i]);
		fprintf(fw, "%s\n", strPreg);
		free(strPreg);
	}

	fclose(fw);
}

char* preguntaParaFichero(Pregunta p) {
	int longStr = 600;
	char *str = malloc(sizeof(char) * longStr);
	sprintf(str, "%s\t%s\t%s\t%s\t%s\t%s\t%i", generarCodigo(p), p.preg,
			p.ops[0], p.ops[1], p.ops[2], p.ops[3], p.res);
	return str;
}

