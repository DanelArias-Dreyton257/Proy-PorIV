/*
 * pregunta.h
 *
 *  Created on: 15 mar. 2021
 *      Author: jon ander y danel
 */

#ifndef PREGUNTA_H_
#define PREGUNTA_H_

#include <stdio.h>
#include "pregunta.h"
#include "string.h"
#include <stdlib.h>

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

#endif /* PREGUNTA_H_ */
