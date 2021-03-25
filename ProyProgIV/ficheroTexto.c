/*
 * ficheroTexto.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */
#include "pregunta.h"

#define NUM_MAX_P 5

//Array provisional para la preparacion de funciones
Pregunta preguntas[NUM_MAX_P];
int numPreguntas = 0;

/**
 * Busca una pregunta concreta en el fichero de texto y la devuelve
 *
 * @param char* que contiene el codigo de la pregunta que se quiere buscar
 * @return pregunta leida de fichero correpondiete a ese codigo
 */
Pregunta buscarPreguntaEnFichero(char *codigo) {
	//TODO hacer la busqueda real
	return generarPreguntaPrueba();
}

/**
 * Inserta una pregunta en el fichero de texto
 * @param pregunta a escribir
 */
void insertarPregunta(Pregunta p){
	if (numPreguntas<NUM_MAX_P){

		preguntas[numPreguntas] = p;

		numPreguntas++;
	}
}
/**
 * Borra una pregunta del fichero de texto
 * @param codigo que representa a la pregunta a borrar
 */
void borrarPregunta(char* codigo){
	//PROVISIONAL CAMBIAR MAS ADELANTE
}
/**
 * Imprime todas las perguntas almacenadas, una detras de otra
 */
void printTodasPreguntas(){
	for (int i= 0; i<numPreguntas;i++){
		printPregunta(&preguntas[i]);
	}
}

