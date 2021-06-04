/*
 * Usuario.cpp
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#include "Usuario.h"
#include <string.h>
#include <iostream>
using namespace std;

Usuario::Usuario(char *nombre) :
		Jugador(nombre, VIDA_BASE) {
}
Usuario::Usuario(char *nombre, int puntuacion) :
		Jugador(nombre, VIDA_BASE) {
	this->puntuacion = puntuacion;
}

Usuario::Usuario(const Usuario &other) :
		Jugador(other) {
	this->puntuacion = puntuacion;
}

Usuario::~Usuario() {
}

void Usuario::danyar() {
	vida -= DANYO;
}

int Usuario::getPuntuacion() const {
	return puntuacion;
}

void Usuario::setPuntuacion(int puntuacion = 0) {
	this->puntuacion = puntuacion;
}

const int Usuario::getVidaBase() {
	return VIDA_BASE;
}

void Usuario::revitalizar() {
	vida += INC_RECU;
}

void Usuario::print() {
	cout << nombre << "[Punt:" << puntuacion << "]" << vidaToString()
			<< endl;
}

