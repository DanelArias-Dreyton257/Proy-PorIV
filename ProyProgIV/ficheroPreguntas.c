/*
 * ficheroTexto.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */

#include "ficheroPreguntas.h"
#include "pregunta.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"

#define NOMBRE_FIC "ficheroPreguntas.txt"
#define INC_POS 10
#define INT_MAX 2147483647

//Array de almacenamiento
Pregunta *preguntas = NULL;

int numPreguntas = 0;
int numeroMax = 0;

/**
 * Busca una pregunta concreta en el fichero de texto y devuelve un puntero a esta
 *
 * @param char* que contiene el codigo de la pregunta que se quiere buscar
 * @return puntero a pregunta leida de fichero correpondiete a ese codigo, si no se ha encontrado devuelve un a NULL
 */
Pregunta* buscarPregunta(char *codigo) {

	int posEncontrado = buscarPosPregunta(codigo);

	if (posEncontrado < 0) { //En caso de que no se encuentre la pregunta buscada
		return NULL;
	} else {
		return preguntas + posEncontrado; //En caso de encontrarla devuelve el puntero a esta
	}
}
/**
 * Busca una pregunta segun su codigo, devolvera la pregunta con el codigo mas parecido al introducido
 *
 * @param char* que contiene el codigo parecido al de la pregunta que se quiere buscar
 * @return puntero a pregunta leida de fichero correpondiete a ese codigo, si no se ha encontrado devuelve un a NULL
 */
Pregunta* buscarPreguntaParecida(char *codigo) {

	int posEncontrado = buscarPosPreguntaMin(codigo);

	if (posEncontrado < 0) { //En caso de que no se encuentre la pregunta buscada
		return NULL;
	} else {
		return preguntas + posEncontrado; //En caso de encontrarla devuelve el puntero a esta
	}
}
/**
 * Busca la posicion de en la array de la pregunta segun el codigo pasado como parametro
 * @param codigo de la pregunta
 * @return posicion de la pregunta en la array, -1 si no encontrado
 */
int buscarPosPregunta(char *codigo) {
	int posEncontrado = -1;
	for (int i = 0; i < numPreguntas; i++) {
		if (strcmp(generarCodigo(preguntas[i]), codigo) == 0) { //Si el codigo es el mismo
			posEncontrado = i;
			break;
		}
	}
	return posEncontrado;
}
/**
 * Busca la posicion de en la array de la pregunta con el codigo mas proximo segun el codigo pasado como parametro
 * @param codigo de la pregunta
 * @return posicion de la pregunta en la array
 */
int buscarPosPreguntaMin(char *codigo) { //FIXME no funciona totalmente bien
	int posEncontrado = -1;
	int min = INT_MAX;

	for (int i = 0; i < numPreguntas; i++) {
		int comp = abs(distanciaStrs(generarCodigo(preguntas[i]), codigo));
		if (comp < min) { //Si la comparacion da un numero menor
			posEncontrado = i;
			min = comp;
		}
	}
	return posEncontrado;
}
/**
 * Devuelve la distancia entre 2 strings comparando sus caracteres
 * @param str1 primer string
 * @param str2 segundo string
 * @return distancia entre los strings
 */
int distanciaStrs(char *str1, char *str2) { //FIXME no funciona 100% bien como querriamos pero es una apanyo
	int i = 0, count = 0;

	while (str1[i] != '\0' || str2[i] != '\0') {
		count += str1[i] - str2[i];
		i++;
	}

	//se anyaden los caracteres "extra" si es que hay
	int j = i, k = i;

	while (str1[j] != '\0') {
		count += str1[j];
	}
	while (str2[k] != '\0') {
		count -= str2[k];
	}
	return count;
}

/**
 * Inserta una pregunta en el fichero de texto
 * @param pregunta a escribir
 */
void insertarPregunta(Pregunta p) {
	//Si no ha reservado previamente memoria para la array
	if (preguntas == NULL) {
		numeroMax = INC_POS;
		preguntas = malloc(sizeof(Pregunta) * numeroMax);
	}
	//Mientras no se supere el maximo
	if (numPreguntas < numeroMax) {

		preguntas[numPreguntas] = p;

		numPreguntas++;

		quickSortPreguntasPorCodigo(preguntas, numPreguntas); //ordena las preguntas

	} else { //Si se supera el maximo es necesario reservar mas sitio

		numeroMax += INC_POS;
		Pregunta *preguntasRealloc = realloc(preguntas,
				sizeof(Pregunta) * numeroMax); //Reserva para para 10 preguntas mas que antes

		preguntas = preguntasRealloc;

		insertarPregunta(p); //La pregunta ya se puede almacenar
	}
}
/**
 * Borra una pregunta del fichero de texto. Si no se encuentra la pregunta, no hace nada
 * @param codigo que representa a la pregunta a borrar
 */
void borrarPregunta(char *codigo) {

	int posEncontrado = buscarPosPregunta(codigo);

	if (posEncontrado >= 0) {
		//Eliminar y mover hacia la izquierda
		for (int i = posEncontrado; i < numPreguntas - 1; i++) {
			preguntas[i] = preguntas[i + 1];
		}
		numPreguntas--;
	} else {
		printf("Pregunta no encontrada");
	}
}
/**
 * Imprime todas las perguntas almacenadas, una detras de otra
 */
void printTodasPreguntas() {
	printf("Hay %i preguntas almacenadas:\n", numPreguntas);
	//fflush(stdout);
	for (int i = 0; i < numPreguntas; i++) {
		printPregunta(&preguntas[i]);
		printf("\n");
		//fflush(stdout);
	}
}
/**
 * Carga las preguntas del fichero y las guarda en la array
 */
void cargarPreguntas() {

	FILE *fr = fopen(NOMBRE_FIC, "r");

	int comp = fscanf(fr, "%i\n", &numeroMax); //Lee el numero de preguntas y lo asume como maximo

	if (comp != EOF) { //Si no hay nada guardado
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
			fscanf(fr,
					"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",
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
	}
	fclose(fr);
}
/**
 * Almacena las preguntas de la array en un fichero de texto
 */
void guardarPreguntas() {

	//Ordena las preguntas segun el codigo
	quickSortPreguntasPorCodigo(preguntas, numPreguntas);

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
/**
 * Intercambia los valores de entre dos preguntas
 * @param puntero a pregunta 1
 * @param puntero a pregunta 2
 */
void swap_ptrs(Pregunta *arg1, Pregunta *arg2) {
	Pregunta tmp = *arg1;
	*arg1 = *arg2;
	*arg2 = tmp;
}
/**
 * Ordena las preguntas de la array pasada como parametro segun el codigo de estas
 * El algoritmo utilizado es quicksort (recursivamente)
 *
 * @param puntero al inicio de la array
 * @param longitud de la array
 */
void quickSortPreguntasPorCodigo(Pregunta *args, int len) {
	int i, pvt = 0;

	if (len <= 1)
		return;

	//Coge el primer valor y lo manda a la ultima posicion
	swap_ptrs(args, args + len - 1);

	// Resetea el indice de pivote a 0 y luego empieza a comparar
	for (i = 0; i < len - 1; ++i) {
		if (strcmp(generarCodigo(args[i]), generarCodigo(args[len - 1])) < 0)
			swap_ptrs(args + i, args + pvt++);
	}

	// Pone el pivote en su sitio
	swap_ptrs(args + pvt, args + len - 1);

	//Llamada a a continuar. No se incluye la posicion del pivote
	quickSortPreguntasPorCodigo(args, pvt++);
	quickSortPreguntasPorCodigo(args + pvt, len - pvt);
}
/**
 * Libera el la array de preguntas
 */
void liberarPreguntas() {

	for (int i = 0; i < numPreguntas; i++) { //Libera cada pregunta almacenada
		Pregunta p = preguntas[i];
		free(p.cat);
		free(p.preg);
		for (int j = 0; j < N_OPCS; j++) { //Libera las opciones
			free(p.ops[j]);
		}
	}
	free(preguntas);
}
/**
 * Devuelve un puntero a una pregunta aleatoria del array
 * @return puntero a la pregunta
 */
Pregunta* getPreguntaAleatoria() {
	int posRnd = rand() % numPreguntas;
	return preguntas + posRnd;
}
