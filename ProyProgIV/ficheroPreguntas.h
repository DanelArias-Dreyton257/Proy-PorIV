/*
 * ficheroTexto.h
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */

#ifndef FICHEROPREGUNTAS_H_
#define FICHEROPREGUNTAS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "pregunta.h"

#define NUM_C_STR 200 //Numero de caracteres maximo para char*

Pregunta* buscarPregunta(char *codigo);
void insertarPregunta(Pregunta p);
void borrarPregunta(char *codigo);
void printTodasPreguntas();
int buscarPosPregunta(char *codigo, Categoria *c);
void cargarPreguntas();
void guardarPreguntas(int copia);
void quickSortCategorias(Categoria *args, int len);
void liberarPreguntas();
int buscarPosPreguntaMin(char *codigo, Categoria *c);
int buscarPosCategoria(char *cat);
Pregunta* buscarPreguntaParecida(char *codigo);
void printNombresCategorias();
Categoria* getCategorias(int *numeroCategorias);
void eliminarFichero();
int getTotalPreguntas();

#ifdef __cplusplus
}
#endif

#endif /* FICHEROPREGUNTAS_H_ */
