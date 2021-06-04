/*
 * juego.cpp
 *
 *  Created on: 23 may. 2021
 *      Author: danel
 */
#include "Jugador.h"
#include "Usuario.h"
#include <iostream>
#include "baseDatos.h"
#include "Asignatura.h"

using namespace std;

Asignatura **asigs = NULL;
Usuario *u = NULL;
int numAsig = 0;

void printEstadoJugadores(Jugador &j1, Jugador &j2) {
	j1.print(); //TODO
	j2.print();
}

void initAsignaturas() {

	char **array = NULL;
	getNomCategorias(&array, &numAsig);

	asigs = new Asignatura*[numAsig];

	for (int i = 0; i < numAsig; i++) {
		asigs[i] = new Asignatura(array[i]);
	}
}

void jugar(char *nombre) {
	u = new Usuario(nombre);
	initAsignaturas();
	//TODO
}

