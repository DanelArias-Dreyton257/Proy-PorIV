/*
 * string.c
 *
 *  Created on: 18 mar. 2021
 *      Author: danel
 */
#include <stdio.h>
#include <stdlib.h>

void imprimir(char *s) {
	int i = 0;
	while (*(s + i) != '\0') {
		printf("%c", *(s + i));
		i++;
	}
}
int longitud(char *s) {
	int i = 0;
	while (*(s + i) != '\0') {
		i++;
	}
	return i;
}
void copiar(char *dest, char *origen) {
	int i = 0;
	while (*(origen + i) != '\0') {
		*(dest + i) = *(origen + i);
		i++;
	}
	*(dest + i) = '\0';
}
void concat(char *dest, char *origen) {
	copiar(dest+longitud(dest),origen);
}
char* clonar(char *s) {
	char *d = malloc(sizeof(char) * (longitud(s) + 1));
	copiar(d,s);
	return d;
}

