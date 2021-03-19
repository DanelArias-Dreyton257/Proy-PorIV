/*
 * ficheroTexto.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel
 */
#include "pregunta.h"

Pregunta buscarPreguntaEnFichero(char *codigo) {
	//TODO hacer la busqueda real
	char *lista[] = { "PA", "¿Es esto una pregunta de prueba?", "Claro que si",
			"Quien sabe", "Si y No, la pregunta de Schrodinger",
			"Pero te queremos igual", "1" };
	return crearPregunta(lista);
}

