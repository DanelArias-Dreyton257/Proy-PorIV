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

Usuario::Usuario(char *nombre, char *contrasena) :
		Jugador(nombre, VIDA_BASE) {
	this->contrasena = strdup(contrasena);
}

char* Usuario::getContrasena() const {
	return contrasena;
}

Usuario::Usuario(const Usuario &other) :
		Jugador(other) {
	this->contrasena = strdup(other.contrasena);
}

Usuario::~Usuario() {
	delete[] contrasena;
}

void Usuario::danyar() {
	vida -= DANYO;
}

int Usuario::getRecord() const {
	return record;
}

void Usuario::setRecord(int newRecord) {
	this->record = record;
}

bool Usuario::isNewRecord(int newRecord) {
	return newRecord > record;
}
bool Usuario::checkContrasena(char *contrasena) {

	if (strlen(contrasena) != strlen(this->contrasena)) {
		return false;
	}

	for (unsigned int i = 0; i < strlen(this->contrasena); i++) {
		if (contrasena[i] != this->contrasena[i]) {
			return false;
		}
	}

	return true;

}

const int Usuario::getVidaBase() {
	return VIDA_BASE;
}

void Usuario::revitalizar() {
	vida += INC_RECU;
}

void Usuario::print() {
	cout << nombre << "(pwd:" << contrasena << "):" << vidaToString() << endl;
}

