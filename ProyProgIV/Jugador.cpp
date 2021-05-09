/*
 * Jugador.cpp
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#include "Jugador.h"

Jugador::Jugador(char *nombre) {
	this->nombre = nombre;
	this->vida = VIDA_MAX;
}

char* Jugador::getNombre() const {
	return nombre;
}

void Jugador::setNombre(char *nombre) {
	this->nombre = nombre;
}

int Jugador::getVida() const {
	return vida;
}

void Jugador::setVida(int vida) {
	this->vida = vida;
}

const int Jugador::getVIDA_MAX() {
		return VIDA_MAX;
}

Jugador::~Jugador() {
	delete nombre;
}



