/*
 * menu.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel
 */
#include <stdio.h>
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
	char *ops[] = { "\n\t1.Gestion de preguntas y respuestas",
			"\n\t2.Jugar (No disponible)", "\n\t3.Salir\n" };
	char *t = "\nIntroduce tu seleccion (1-3):\n";

	printf("%s", q);
	for (int i = 0; i<3; i++){
		printf("%s",ops[i]);
	}
	printf("%s",t);

	int s = getIntInput();

	switch (s) {
	default:
		return;
	case 1:
		printf("Elegiste Gestion");
		break;
	case 2:
		printf("Elegiste Jugar");
		break;
	case 3:
		return;
	}
}

