/*
 * ficheroTexto.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */
#include "pregunta.h"
/**
 * Busca una pregunta concreta en el fichero de texto y la devuelve
 *
 * @param char* que contiene el codigo de la pregunta que se quiere buscar
 * @return pregunta leida de fichero correpondiete a ese codigo
 */
Pregunta buscarPreguntaEnFichero(char *codigo) {
	//TODO hacer la busqueda real
	char *lista[] = { "PA", "¿Es esto una pregunta de prueba?", "Claro que si",
			"Quien sabe", "Si y No, la pregunta de Schrodinger",
			"Pero te queremos igual", "1" };
	return crearPregunta(lista);
}

