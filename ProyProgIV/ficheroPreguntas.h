/*
 * ficheroTexto.h
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */

#ifndef FICHEROPREGUNTAS_H_
#define FICHEROPREGUNTAS_H_

#include "pregunta.h"

#define NUM_C_STR 100 //Numero de caracteres maximo para char*

Pregunta* buscarPreguntaEnFichero(char *codigo);
void insertarPregunta(Pregunta p);
void borrarPregunta(char *codigo);
void printTodasPreguntas();
int buscarPosPregunta(char *codigo);
void cargarPreguntas();
void guardarPreguntas();
char* preguntaParaFichero(Pregunta p);
void quickSortPreguntasPorCodigo(Pregunta *args, int len);
void swap_ptrs(Pregunta *arg1, Pregunta *arg2);
void liberarPreguntas();

#endif /* FICHEROPREGUNTAS_H_ */
