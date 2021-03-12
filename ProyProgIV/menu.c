/*
 * menu.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel
 */
#include <stdio.h>
#include "menu.h"

char getCharInput() {
	char chr;
	scanf("%c", &chr);
	return chr;
}
int getIntInput() {
	int i;
	scanf("%i", &i);
	return i;
}

void menuPrincipal() {

	char *q = "\nMenu Principal";
	char *ops[] = { "Gestion de preguntas y respuestas",
			"Jugar (No disponible)", "Salir" };
	char *t = "\nIntroduce tu seleccion (1-3):\n";

	printf("%s", q);
	printOpciones(ops, 3);
	printf("%s", t);

	int s = getIntInput();

	switch (s) {
	default:
		return;
	case 1:
		menuGestion();
		break;
	case 2:
		printf("Elegiste Jugar");
		break;
	case 3:
		return;
	}
}

void menuGestion() {

	char *q = "\nMenu Gestion de Preguntas";
	char *ops[] = { "Crear preguntas", "Borrar preguntas",
			"Modificar Preguntas", "Ver preguntas creadas",
			"Volcar fichero de texto a BD", "Volver" };
	char *t = "\nIntroduce tu seleccion (1-6):\n";

	printf("%s", q);
	printOpciones(ops, 6);
	printf("%s", t);

	int s = getIntInput();

	switch (s) {
	default:
		return;
	case 1:
		printf("Elegiste Crear");
		break;
	case 2:
		printf("Elegiste Borrar");
		break;
	case 3:
		printf("Elegiste Modificar");
		break;
	case 4:
		printf("Elegiste Ver las preguntas");
		break;
	case 5:
		printf("Elegiste Volcar a BD");
		break;
	case 6:
		menuPrincipal();
		break;
	}
}

void printOpciones(char *ops[], int size) {
	for (int i = 0; i < size; i++) {
		printf("\n\t%i.%s", i + 1, ops[i]);
	}
}

