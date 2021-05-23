/*
 * pregunta.h
 *
 *  Created on: 15 mar. 2021
 *      Author: jon ander y danel
 */

#ifndef PREGUNTA_H_
#define PREGUNTA_H_

#ifdef __cplusplus
extern "C" {
#endif

#define N_LISTA_PREG 7
#define N_OPCS 4

typedef struct {
	char *cat;
	char *preg;
	char **ops;
	int res;

} Pregunta;

typedef struct {
	char *nombre;
	Pregunta *preguntas;
	int numPreguntas;
} Categoria;

void printPregunta(Pregunta *p);
void printPreguntaJuego(Pregunta *p);
Pregunta crearPregunta(char *list[]);
void freeRespuestas(Pregunta *p);
void freePregunta(Pregunta *p);
char* generarCodigo(Pregunta p);
Pregunta generarPreguntaPrueba();
void insertarPreguntaEnCategoria(Pregunta p, Categoria *c);
void printCategoria(Categoria *c);

int comprobarCategoria(char* cat);
int comprobarPregunta(char* preg);
int comprobarOpcion(char* opc);
int comprobarCodOpcion(int codRes);
int comprobarPreguntaEntera(Pregunta *p);

int esRespuestaCorrecta(Pregunta *p, int res);

char* categoriaDesdeCodigo(char *codigo);

Pregunta duplicarPregunta(Pregunta *preg);

#ifdef __cplusplus
}
#endif

#endif /* PREGUNTA_H_ */
