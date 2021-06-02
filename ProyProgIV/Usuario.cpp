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

Usuario::Usuario(char *nombre, char *contrasena, int record) :
		Jugador(nombre, VIDA_BASE) {
	this->contrasena = strdup(contrasena);
	this->record = record;
}
Usuario::Usuario(char *nombre, char *contrasena, int record, int puntuacion) :
		Jugador(nombre, VIDA_BASE) {
	this->contrasena = strdup(contrasena);
	this->record = record;
	this->puntuacion = puntuacion;
}

char* Usuario::getContrasena() const {
	return contrasena;
}

Usuario::Usuario(const Usuario &other) :
		Jugador(other) {
	this->contrasena = strdup(other.contrasena);
	this->record = other.record;
	this->puntuacion = puntuacion;
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

bool Usuario::isNewRecord() {
	return puntuacion > record;
}

int Usuario::getPuntuacion() const {
	return puntuacion;
}

void Usuario::setPuntuacion(int puntuacion = 0) {
	this->puntuacion = puntuacion;
}

bool Usuario::checkContrasena(char *contrasena) {

	return strcmp(this->contrasena,contrasena) == 0;

}

const int Usuario::getVidaBase() {
	return VIDA_BASE;
}

void Usuario::revitalizar() {
	vida += INC_RECU;
}

void Usuario::print() {
	cout << nombre << "(pwd:" << contrasena << ")[Rec." << record << "][Punt."
			<< puntuacion << "]" << endl << vidaToString() << endl;
}

