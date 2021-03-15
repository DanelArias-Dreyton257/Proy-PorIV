/*
 * menu.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel
 */
#include <stdio.h>
#include "menu.h"
#include "pregunta.h"
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
		menuCrearPregunta();
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

void menuCrearPregunta() {

	char *pasos[] = { "Introduce codigo de categoria:", "Introduce la pregunta:",
			"Introduce respuesta 1:", "Introduce respuesta 2:",
			"Introduce respuesta 3:", "Introduce respuesta 4:",
			"Introduce codigo de respuesta correcta (0-3):" };
	char *lista[7];
	for (int i = 0;  i < 7; i++) {
		printf("\n%s\n",pasos[i]);
		//char s = getCharInput();
		lista[i]="StringPrueba"; //FIXME
	}
	Pregunta p=crearPregunta(lista);
	//TODO
	printPregunta(&p);



}

void printOpciones(char *ops[], int size) {
	for (int i = 0; i < size; i++) {
		printf("\n\t%i.%s", i + 1, ops[i]);
	}
}

