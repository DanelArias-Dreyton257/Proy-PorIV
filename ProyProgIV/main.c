/*
 * main.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */

#include "menu.h"
#include "ficheroPreguntas.h"

/**
 * Main function of the program
 * No argument is received
 *
 * Trello de referencia para cosas por hacer
 * https://trello.com/b/bC6F5mTA/study-with-honors
 */
int main(int argc, char **argv) {

	cargarPreguntas();

	//insertarPregunta(generarPreguntaPrueba());

	//Abre el menu principal
	limpiarConsola();
	menuPrincipal();
	//printTodasPreguntas();

	guardarPreguntas();

	liberarPreguntas();

	return 0;

}

