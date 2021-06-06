/*
 * Asignatura.cpp
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#include "Asignatura.h"
#include <string.h>
#include "baseDatos.h"
#include "sqlite3.h"
#include "pregunta.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

//Crea el mapa de categorias con los nombres de cada asignatura
unordered_map<string, string> Asignatura::mapaCategorias =
	  { { "BD", "Base de datos" },
		{ "MT", "Matematicas" },
		{ "PR", "Programacion" },
		{ "HS", "Historia" },
		{ "AD", "ADE" },
		{ "IN", "Ingles" },
		{ "QC", "Computacion cuantica" },
		{ "FI", "Fisica" },
		{ "BI", "Biologia" },
		{ "IN", "Ingles" },
		{ "EA", "Estructura y Arquitectura de computadores" } };

/**
 * Constructor de asignatura con el codigo de 2 letras de la asignatura en cuestion
 * @param cat, char* con el codigo de 2 letras
 */
Asignatura::Asignatura(char *cat) {

	//coger el valor del mapa
	unordered_map<string, string>::const_iterator got = mapaCategorias.find(
			string(cat));
	if (got != mapaCategorias.end()) { //encuentra el valor en el mapa
		this->nombre = strdup(got->second.data());
	} else {
		this->nombre = (char*) "Not Found";
	}

	this->vida = NUM_CREDITOS;
	this->vidaMax = NUM_CREDITOS;

	int res = getPreguntasCategoria(cat, &(this->preguntas),
			&(this->numPreguntas));
	if (res != SQLITE_OK) {
		cout << "Error cargando las preguntas de la BD en asignatura" << endl;
		cerrarBaseDatos();
		return;
	}

}
/**
 * Devuelve el numero de creditos de la asignatura
 * @return NUM_CREDITOS
 */
const int Asignatura::getNumCreditos() {
	return NUM_CREDITOS;
}

/**
 * Constructor copia de la asignatura
 */
Asignatura::Asignatura(const Asignatura &other) :
		Jugador(other) {
	this->preguntas = new Pregunta[other.numPreguntas];
	this->numPreguntas = other.numPreguntas;
	for (int i = 0; i < other.numPreguntas; i++) {
		this->preguntas[i] = duplicarPregunta(&other.preguntas[i]);
	}
}
/**
 * Destructor de la asignatura
 */
Asignatura::~Asignatura() {
	for (int i = 0; i < numPreguntas; i++) {
		freePregunta(preguntas + i);
	}
	delete[] preguntas;
}

/**
 * Reduce la vida de la asinatura, segun el danyo
 */
void Asignatura::danyar() {
	vida -= DANYO;
}

/**
 * Saca por consola la asignatura
 */
void Asignatura::print() {
	cout << nombre << "(" << NUM_CREDITOS << " creditos):" << endl << "\t"
			<< vidaToString() << endl;
}
/**
 * Saca por consola las preguntas de la asignatura
 */
void Asignatura::printPreguntas() {
	cout << nombre << "(" << numPreguntas << "):" << endl;
	for (int i = 0; i < numPreguntas; i++) {
		cout << "\t";
		printPregunta(preguntas + i);
		cout << "\n";
	}
}

/**
 * Restaura la vida de la asignatura devolviendola a vidaMax
 */
void Asignatura::restaurar() {
	this->vida = vidaMax;
}
/**
 * Devuelve una pregunta elegida aleatoriamente
 * @return puntero a la pregunta elegida
 */
Pregunta* Asignatura::getPreguntaRandom() {
	int i = rand() % this->numPreguntas;
	return this->preguntas + i;
}

