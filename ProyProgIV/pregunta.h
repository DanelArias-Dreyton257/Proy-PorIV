/*
 * pregunta.h
 *
 *  Created on: 15 mar. 2021
 *      Author: jon ander y danel
 */

#ifndef PREGUNTA_H_
#define PREGUNTA_H_

#include "pregunta.h"
//#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

#define N_LISTA_PREG 7
#define N_OPCS 4

typedef struct {
	char *cat;
	char *preg;
	char **ops;
	int res;

} Pregunta;

void printPregunta(Pregunta *p);
Pregunta crearPregunta(char *list[]);
void freeRespuestas(Pregunta *p);
char* generarCodigo(Pregunta p);
Pregunta generarPreguntaPrueba();

#endif /* PREGUNTA_H_ */
