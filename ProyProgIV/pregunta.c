/*
 * pregunta.c
 *
 *  Created on: 15 mar. 2021
 *      Author: jon ander y danel
 */
#include <stdio.h>
#include "pregunta.h"
#include "string.h"
#include <stdlib.h>
/**
 * Saca por consola la informacion de la pregunta pasada como parametro
 *
 * CATEGORIA:
 * �Pregunta pregunta pregunta?:
 * 	opcion1
 * 	opcion2
 * 	opcion3
 * 	opcion4
 * numRes->opcionRes
 *
 * @param puntero a la pregunta a imprimir
 */
void printPregunta(Pregunta *p) {
	printf("%s:\n%s:\n\t %s,\n\t %s,\n\t %s,\n\t %s,\n %i->%s", p->cat, p->preg,
			*(p->ops), *(p->ops + 1), *(p->ops + 2), *(p->ops + 3), p->res,
			*(p->ops + p->res));
}
/**
 * Crea una pregunta segun la array de char* que recibe con la informacion de la pregunta
 *
 * @param char* list[] lista de char* de tama�o N_LISTA_PREG con la informacion de la pregunta en orden: categoria, pregunta, opcion0, opcion1, opcion2, opcion3, numOpcionCorrecta
 * @return Pregunta con la informacion introducida
 */
Pregunta crearPregunta(char *list[]) {
	Pregunta p;

	p.cat = list[0];
	p.preg = list[1];

	char **ops = malloc(sizeof(char*) * N_OPCS);

	for (int i = 0; i < N_OPCS; i++) {
		*(ops + i) = clonar(list[2 + i]);
	}

	p.ops = ops;

	p.res = atoi(list[6]);

	return p;
}
/**
 * Libera la memoria dinamica usada para el almacenamiento de las respuestas
 *
 * @param puntero de a la pregunta que se quiera liberar
 */
void freeRespuestas(Pregunta *p) {
	for (int i = 0; i < N_OPCS; i++) {
		free(*(p->ops + i));
	}
	free(p->ops);
}