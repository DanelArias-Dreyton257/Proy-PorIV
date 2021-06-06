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

/**
 * Constructor de jugador sin ningun dato
 */
Jugador::Jugador() {
	this->nombre = NULL;
	this->vida = 0;
	this->vidaMax = 0;
}

/**
 * Constructor de jugador con el nombre y la vida maxima del jugador en cuestion
 * @param nombre, char* con el nombre del jugador
 * @param vidaMax, int con la vida maxima del jugador
 */
Jugador::Jugador(char *nombre, int vidaMax) {
	this->nombre = strdup(nombre);
	this->vida = vidaMax;
	this->vidaMax = vidaMax;
}

/**
 * Constructor copia del jugador
 */
Jugador::Jugador(const Jugador &other) {
	this->nombre = strdup(other.nombre);
	this->vida = other.vida;
	this->vidaMax = other.vidaMax;
}

/**
 * Devuelve el nombre del jugador
 * @return el nombre del jugador
 */
char* Jugador::getNombre() const {
	return nombre;
}

/**
 * Establece el nombre del jugador
 */
void Jugador::setNombre(char *nombre) {
	this->nombre = nombre;
}

/**
 * Devuelve la vida del jugador
 * @return la vida del jugador
 */
int Jugador::getVida() const {
	return vida;
}


/**
 * Establece la vida del jugador
 */
void Jugador::setVida(int vida) {
	this->vida = vida;
}

/**
 * Devuelve la vida maxima del jugador
 * @return la vida maxima del jugador
 */
const int Jugador::getVidaMax() const {
	return vidaMax;
}

/**
 * Destructor del jugador
 */
Jugador::~Jugador() {
	delete[] nombre;
}

/**
 * Devuelve true si el jugador tiene 0 o menos vida
 * @return true si el jugador tiene 0 o menos vida
 */
bool Jugador::isMuerto() {
	return vida <= 0;
}

/**
 * Devuelve la informacion visual como barras de vida, nombre del usuario, cantidad de vida, y si esta derrotado o no
 * @return barras de vida, nombre del usuario, cantidad de vida, y si esta derrotado o no
 */
char* Jugador::vidaToString() {
	int numCharBarra = 50;
	char *str = new char[4 + numCharBarra + 1 + 9 + 1];
	if (isMuerto()) {
		sprintf(str,"DERROTADO");
	} else {
		sprintf(str, "HP:[");
		float porc = ((float)vida)/((float)vidaMax);
		int numCharVida = ceil(porc * numCharBarra);
		int initLen = strlen(str);
		for(int i=0; i<numCharBarra; i++){
			char c;
			if (i<numCharVida){
				c = '/';
			}
			else{
				c = '_';
			}
			str[initLen + i] = c;
		}
		str[initLen + numCharBarra] = ']';
		str[initLen + numCharBarra + 1] = '\0';
		sprintf(str,"%s(%i,%i)",str,vida,vidaMax);
	}
	return str;
}

