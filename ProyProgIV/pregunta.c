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
void printPregunta(Pregunta *p) {//FIXME
	printf("- \"%s\" - %s:\n", generarCodigo(*p), p->preg);

	for (int i = 0; i < N_OPCS; i++) {
		printf("\t%c. %s,\n", 'A' + i, *(p->ops + i));
	}

	printf("\tR:(%c)->%s\n", 'A' + p->res, *(p->ops + p->res));

	//fflush(stdout);

}
/**
 * Saca por consola la informacion de la pregunta pasada como parametro sin mostrar la respuesta
 *
 * -"codigo"-¿Pregunta pregunta pregunta?:
 * 	opcion1
 * 	opcion2
 * 	opcion3
 * 	opcion4
 *
 * @param puntero a la pregunta a imprimir
 */
void printPreguntaJuego(Pregunta *p) { //FIXME
	printf("- \"%s\" - %s:\n", generarCodigo(*p), p->preg);

	for (int i = 0; i < N_OPCS; i++) {
		printf("\t%c. %s,\n", 'A' + i, *(p->ops + i));
	}
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
/**
 * Libera la memoria usada para el almacenamiento de la pregunta
 *
 * @param puntero de a la pregunta que se quiera liberar
 */
void freePregunta(Pregunta *p) {
	free(p->cat);
	free(p->preg);
	freeRespuestas(p);
}
/**
 * Genera el char* con el codigo que representa la pregunta
 * @param p Pregunta de la cual se quiere sacar el codigo
 * @return char* con el codigo
 */
char* generarCodigo(Pregunta p) {
	int longCod = 11;
	char noneChar = 'N';
	char *cod = malloc(sizeof(char) * (longCod + 1));
	if (comprobarCategoria(p.cat) > 0) { //Si al menos tiene 2 caracteres
		cod[0] = p.cat[0];
		cod[1] = p.cat[1];
	} else {
		cod[0] = noneChar;
		cod[1] = noneChar;
	}
	if (comprobarPregunta(p.preg) > 0) {
		cod[2] = p.preg[1];
		cod[3] = p.preg[2];

		cod[4] = p.preg[strlen(p.preg) - 3];
		cod[5] = p.preg[strlen(p.preg) - 2];
	} else {
		for (int i = 0; i < 4; i++) {
			cod[2 + i] = noneChar;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (comprobarOpcion(p.ops[i]) > 0) {
			cod[6 + i] = (p.ops[i])[0]; //Coge el primer caracter de cada opcion
		} else {
			cod[6 + i] = noneChar;
		}
	}
	if (comprobarCodOpcion(p.res) > 0) {
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
/**
 * Comprueba si la categoria es valida, para ello debe tener al menos 2 caracteres
 * @param puntero al primer caracter del string con la categoria
 * @return devuelve 1 si cumple con los requisitos, sino devuelve 0
 */
int comprobarCategoria(char *cat) {
	if (strlen(cat) >= 2) {
		return 1;
	} else
		return 0;
}
/**
 * Comprueba si la pregunta es valida, para ello debe tener al menos 4 caracteres
 * @param puntero al primer caracter del string con la pregunta
 * @return devuelve 1 si cumple con los requisitos, sino devuelve 0
 */
int comprobarPregunta(char *preg) {
	if (strlen(preg) >= 4) {
		return 1;
	} else
		return 0;
}
/**
 * Comprueba si la opcion es valida, para ello debe tener al menos 1 caracter
 * @param puntero al primer caracter del string con la opcion
 * @return devuelve 1 si cumple con los requisitos, sino devuelve 0
 */
int comprobarOpcion(char *opc) {
	if (strlen(opc) >= 1) {
		return 1;
	} else
		return 0;
}
/**
 * Comprueba si la opcion es valida, para ello debe tener al menos 1 caracter
 * @param puntero al primer caracter del string con la opcion
 * @return devuelve 1 si cumple con los requisitos, sino devuelve 0
 */
int comprobarCodOpcion(int codRes) {
	if (codRes >= 0 && codRes <= 4) {
		return 1;
	} else
		return 0;
}
/**
 * Comprueba si la pregunta tiene contenido valido
 * @param puntero a la pregunta a comprobar
 * @return devuelve 1 si cumple con los requisitos, sino devuelve 0
 */
int comprobarPreguntaEntera(Pregunta *p) {
	if (comprobarCategoria(p->cat) > 0 && comprobarPregunta(p->preg) > 0
			&& comprobarOpcion(p->ops[0]) > 0 && comprobarOpcion(p->ops[1]) > 0
			&& comprobarOpcion(p->ops[2]) > 0 && comprobarOpcion(p->ops[3]) > 0
			&& comprobarCodOpcion(p->res) > 0) {
		return 1;
	} else
		return 0;

}
/**
 * Comprueba que la respuesta introducida es valida
 * @param p Puntero a la pregunta que se responde
 * @param res entero con la respuesta indicada entre 1 y 4
 * @return 0 si no se cumple la condicion, 1 si si que se cumple
 */
int esRespuestaCorrecta(Pregunta *p, int res) {
	if (comprobarCodOpcion(res) > 0) {
		if (res == p->res) {
			return 1;
		} else
			return 0;
	} else
		return 0;
}
/**
 * Devuelve la cadena de caracteres con la categoria desde el codigo de la pregunta
 * @param codigo de una categoria generado por el metodo generarCodigo()
 * @return nombre de categoria
 */
char* categoriaDesdeCodigo(char *codigo) {
	if (strlen(codigo) >= 2) {
		char *cat = malloc(sizeof(char) * (2 + 1));
		cat[0] = codigo[0];
		cat[1] = codigo[1];
		cat[2] = '\0';
		return cat;
	}
	return NULL;

}
/**
 * Inserta una pregunta en la categoria indicada reservando la memoria correspondiente
 * @param p, pregunta a anyadir
 * @param *c, puntero a la categoria donde anyadir la pregunta
 */
void insertarPreguntaEnCategoria(Pregunta p, Categoria *c) {
	c->numPreguntas++;
	Pregunta *reallocPregs = realloc(c->preguntas,
			sizeof(Pregunta) * c->numPreguntas);
	c->preguntas = reallocPregs;
	c->preguntas[c->numPreguntas - 1] = p;
}
/**
 * Saca por consola la categoria y sus preguntas
 * @param *c, puntero a la categoria
 */
void printCategoria(Categoria *c) {
	printf("%s : Tiene %i preguntas.\n", c->nombre, c->numPreguntas);
	for (int i = 0; i < c->numPreguntas; i++) {
		printf("\n\t");
		printPregunta(c->preguntas + i);
		printf("\n");
		fflush(stdout);
	}
}

Pregunta duplicarPregunta(Pregunta *preg) {
	char res = preg->res + '0';
	char *list[] = { strdup(preg->cat), strdup(preg->preg), strdup(
			preg->ops[0]), strdup(preg->ops[1]), strdup(preg->ops[2]), strdup(
			preg->ops[3]), &res };
	return crearPregunta(list);
}

