/*
 * string.h
 *
 *  Created on: 18 mar. 2021
 *      Author: danel
 */

#ifndef STRING_H_
#define STRING_H_
#include <stdio.h>
#include <stdlib.h>

void imprimir(char* s);
int longitud(char* s);
void copiar(char* dest, char* origen);
void concat(char* dest, char* origen);
char* clonar(char* s);


#endif /* STRING_H_ */
