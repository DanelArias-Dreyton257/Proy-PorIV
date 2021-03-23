/*
 * string.c
 *
 *  Created on: 18 mar. 2021
 *      Author: danel y jon ander
 */
#include <stdio.h>
#include <stdlib.h>
/**
 * Saca por consola el char* imprimiendo cada caracter
 * @param char* a imprimir
 */
void imprimir(char *s) {
	int i = 0;
	while (*(s + i) != '\0') {
		printf("%c", *(s + i));
		i++;
	}
}
/**
 * Devuelve un entero con la cantidad de caracteres de el char* pasado como paramtero, no tiene en cuenta el '\0' final
 * @param char*
 * @return longitud del char* pasado como parametro
 */
int longitud(char *s) {
	int i = 0;
	while (*(s + i) != '\0') {
		i++;
	}
	return i;
}
/**
 * Copia los caracteres del char* de origen en el char* de destino
 * @param dest char* con longitud>=longitud de char* origen. Donde se copiara
 * @param origen char* con los caracteres que serán copiados en dest
 */
void copiar(char *dest, char *origen) {
	int i = 0;
	while (*(origen + i) != '\0') {
		*(dest + i) = *(origen + i);
		i++;
	}
	*(dest + i) = '\0';
}
/**
 * Concatena los caracteres del char* de dest con el char* origen. A partir del último caracter de dest, se iran añadiendo los de origen consecutivamente
 * @param dest char* con capacidad >= longitud inicial de dest + longitud de origen
 * @param origen char* con los caracteres que seran concatenados en dest
 */
void concat(char *dest, char *origen) {
	copiar(dest + longitud(dest), origen);
}
/**
 * Genera, reservando espacio en memoria dinamica, y devuelve un char* con los mismos caracteres que el que recibe como parametro
 * @param char *s con la secuencia de caracteres a clonar
 * @return char* con la misma secuencia de caracteres de s
 */
char* clonar(char *s) {
	char *d = malloc(sizeof(char) * (longitud(s) + 1));
	copiar(d, s);
	return d;
}

