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
 */
int main(int argc, char **argv) {
	//Abre el menu principal
	insertarPregunta(buscarPreguntaEnFichero("CODPRUEBA"));
	menuPrincipal();

	return 0;

}

