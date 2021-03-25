/*
 * ficheroTexto.h
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */

#ifndef FICHEROTEXTO_H_
#define FICHEROTEXTO_H_

#include "pregunta.h"
#include <stdio.h>

Pregunta buscarPreguntaEnFichero(char *codigo);
void insertarPregunta(Pregunta p);
void borrarPregunta(char* codigo);
void printTodasPreguntas();

#endif /* FICHEROTEXTO_H_ */
