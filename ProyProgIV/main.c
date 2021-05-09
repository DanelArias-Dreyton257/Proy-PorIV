/*
 * main.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */

#include "menu.h"
#include "ficheroPreguntas.h"
#include <stdlib.h>
#include <time.h>

void resetRandomSeed();

/**
 * Main function of the program
 * No argument is received
 *
 * Trello de referencia para cosas por hacer
 * https://trello.com/b/bC6F5mTA/study-with-honors
 */
int main(int argc, char **argv) {

	resetRandomSeed();

	cargarPreguntas();

	//insertarPregunta(generarPreguntaPrueba());

	//Abre el menu principal
	limpiarConsola();

	menuPrincipal();

	if (getTotalPreguntas() > 0) {
		guardarPreguntas(0);
	}

	liberarPreguntas();

	return 0;

}
/**
 * Resetea la seed de la generacion de numeros aleatorios segun el tiempo actual
 */
void resetRandomSeed() {
	srand(time(NULL)); //"Crea" una semilla segun el tiempo para el calculo de numeros aleatorios
}

