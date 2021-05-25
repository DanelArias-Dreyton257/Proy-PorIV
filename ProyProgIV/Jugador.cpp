/*
 * Jugador.cpp
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#include "Jugador.h"
#include <string.h>
#include <cstdio>
#include <cmath>

Jugador::Jugador() {
	this->nombre = NULL;
	this->vida = 0;
	this->vidaMax = 0;
}

Jugador::Jugador(char *nombre, int vidaMax) {
	this->nombre = strdup(nombre);
	this->vida = vidaMax;
	this->vidaMax = vidaMax;
}
Jugador::Jugador(const Jugador &other) {
	this->nombre = strdup(other.nombre);
	this->vida = other.vida;
	this->vidaMax = other.vidaMax;
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

const int Jugador::getVidaMax() const {
	return vidaMax;
}

Jugador::~Jugador() {
	delete[] nombre;
}
bool Jugador::isMuerto() {
	return vida <= 0;
}
char* Jugador::vidaToString() {
	int numCharBarra = 50;
	char *str = new char[13 + numCharBarra + 1+ 1];
	if (isMuerto()) {
		sprintf(str,"DERROTADO");
	} else {
		sprintf(str, "(%i/%i)HP:[", vida, vidaMax);
		float porc = vida/vidaMax;
		int numCharVida = ceil(porc * numCharBarra);
		int initLen = strlen(str);
		for(int i=0; i<numCharBarra; i++){
			char c;
			if (i<numCharVida){
				c = '■';
			}
			else{
				c = '░';
			}
			str[initLen + i] = c;
		}
		str[initLen + numCharBarra] = ']';
		str[initLen + numCharBarra + 1] = '\0';
	}
	return str;
}

