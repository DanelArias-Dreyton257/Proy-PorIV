/*
 * ficheroTexto.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */
#include "pregunta.h"
#include <stdio.h>
#include "ficheroTexto.h"

#define NUM_MAX_P 5
#define NOMBRE_FIC "ficheroPreguntas.dat"

//Array provisional para la preparacion de funciones
Pregunta preguntas[NUM_MAX_P];
int numPreguntas = 0;

FILE *fichero;

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
	if (numPreguntas < NUM_MAX_P) {

		preguntas[numPreguntas] = p;

		numPreguntas++;
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

