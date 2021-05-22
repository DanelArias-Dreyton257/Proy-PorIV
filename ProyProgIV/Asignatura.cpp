/*
 * Asignatura.cpp
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#include "Asignatura.h"

Asignatura::Asignatura(char *nombre):Jugador(nombre, NUM_CREDITOS) {
}

static const int Asignatura::getNumCreditos() const {
	return NUM_CREDITOS;
}

Asignatura::Asignatura(const Asignatura &other):Jugador(other){
}

Asignatura::~Asignatura() {
}

