/*
 * pregunta.c
 *
 *  Created on: 15 mar. 2021
 *      Author: jon ander y danel
 */

#include "pregunta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Saca por consola la informacion de la pregunta pasada como parametro
 *
 * -"codigo"-¿Pregunta pregunta pregunta?:
 * 	opcion1
 * 	opcion2
 * 	opcion3
 * 	opcion4
 *  R:(numRes)->opcionRes
 *
 * @param puntero a la pregunta a imprimir
 */
void printPregunta(Pregunta *p) {
	printf("- \"%s\" - %s:\n\t %s,\n\t %s,\n\t %s,\n\t %s,\n\t R:(%i)->%s",
			generarCodigo(*p), p->preg, *(p->ops), *(p->ops + 1), *(p->ops + 2),
			*(p->ops + 3), p->res, *(p->ops + p->res));
	fflush(stdout);

}
/**
 * Crea una pregunta segun la array de char* que recibe con la informacion de la pregunta
 *
 * @param char* list[] lista de char* de tamaño N_LISTA_PREG con la informacion de la pregunta en orden: categoria, pregunta, opcion0, opcion1, opcion2, opcion3, numOpcionCorrecta
 * @return Pregunta con la informacion introducida
 */
Pregunta crearPregunta(char *list[]) {
	Pregunta p;

	p.cat = list[0];
	p.preg = list[1];

	char **ops = malloc(sizeof(char*) * N_OPCS);

	for (int i = 0; i < N_OPCS; i++) {
		*(ops + i) = strdup(list[2 + i]);
	}

	p.ops = ops;

	p.res = atoi(list[6]) - 1;

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
/**
 * Genera el char* con el codigo que representa la pregunta
 * @param p Pregunta de la cual se quiere sacar el codigo
 * @return char* con el codigo
 */
char* generarCodigo(Pregunta p) {
	int longCod = 11;
	char none = 'N';
	char *cod = malloc(sizeof(char) * (longCod + 1));
	if (strlen(p.cat) >= 2) { //Si al menos tiene 2 caracteres
		cod[0] = p.cat[0];
		cod[1] = p.cat[1];
	} else {
		cod[0] = none;
		cod[1] = none;
	}
	if (strlen(p.preg) >= 4) {
		cod[2] = p.preg[1];
		cod[3] = p.preg[2];

		cod[4] = p.preg[strlen(p.preg) - 3];
		cod[5] = p.preg[strlen(p.preg) - 2];
	} else {
		for (int i = 0; i < 4; i++) {
			cod[2 + i] = none;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (strlen(p.ops[i]) > 0) {
			cod[6 + i] = (p.ops[i])[0]; //Coge el primer caracter de cada opcion
		} else {
			cod[6 + i] = none;
		}
	}
	if (p.res >= 0 && p.res <= 4) {
		cod[10] = p.res + '0'; //Pasar de un entero a un caracter, sumandole el valor del caracter 0
	} else {
		cod[10] = '0';
		//Si no cumple, se asigna el caracter 0 automaticamente
	}
	cod[11] = '\0'; //Se termina la secuencia de caracteres

	return cod;
}
/**
 * Genera una pregunta de prueba con datos de prueba
 * @return pregunta de prueba
 */
Pregunta generarPreguntaPrueba() {
	char *lista[] = { "PB", "¿Es esto una pregunta de prueba?", "Claro que si",
			"Quien sabe", "Si y No, la pregunta de Schrodinger",
			"Averigualo por ti mism@", "0" };

	return crearPregunta(lista);
}
