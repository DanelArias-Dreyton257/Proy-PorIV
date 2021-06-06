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

/**
 * Constructor de usuario con el nombre del usuario en cuestion
 * @param nombre, char* con el nombre del usuario
 */
Usuario::Usuario(char *nombre) :
		Jugador(nombre, VIDA_BASE) {
}

/**
 * Constructor de usuario con el nombre y la puntuacion del usuario en cuestion
 * @param nombre, char* con el nombre del usuario
 * @param puntuacion, int con la puntuacion del usuario
 */
Usuario::Usuario(char *nombre, int puntuacion) :
		Jugador(nombre, VIDA_BASE) {
	this->puntuacion = puntuacion;
}

/**
 * Constructor copia del usuario
 */
Usuario::Usuario(const Usuario &other) :
		Jugador(other) {
	this->puntuacion = puntuacion;
}

/**
 * Destructor del usuario
 */
Usuario::~Usuario() {
}

/**
 * Reduce la vida del usuario, segun el danyo
 */
void Usuario::danyar() {
	vida -= DANYO;
}

/**
 * Devuelve la puntuacion del usuario
 * @return la puntuacion del usuario
 */
int Usuario::getPuntuacion() const {
	return puntuacion;
}

/**
 * Establece la puntuacion del usuario
 */
void Usuario::setPuntuacion(int puntuacion = 0) {
	this->puntuacion = puntuacion;
}

/**
 * Devuelve la vida base del usuario
 * @return la vida base del usuario
 */
const int Usuario::getVidaBase() {
	return VIDA_BASE;
}


/**
 * Aumenta la vida del usuario, segun el INC_RECU
 */
void Usuario::revitalizar() {
	vida += INC_RECU;
	if(vida>vidaMax){
		vida = vidaMax;
	}
}

/**
 * Aumenta en 1  la puntuacion del usuario
 */
void Usuario::incPuntuacion(){
	this->puntuacion++;
}

/**
 * Saca por consola la informacion del usuario
 */
void Usuario::print() {
	cout << nombre << " [Punt:" << puntuacion << "] "<<endl<<"\t" << vidaToString()
			<< endl;
}

