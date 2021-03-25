/*
 * main.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */
#include <stdio.h>
#include "menu.h"
#include "pregunta.h"

/**
 * Main function of the program
 * No argument is received
 *
 * Trello de referencia para cosas por hacer
 * https://trello.com/b/bC6F5mTA/study-with-honors
 */
int main(int argc, char **argv) {

	//Pruebas varias
	//insertarPregunta(buscarPreguntaEnFichero("CODPRUEBA"));
	//printf("%s",generarCodigo(buscarPreguntaEnFichero("")));



	//Abre el menu principal
	menuPrincipal();

	return 0;

}

