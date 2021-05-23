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
using namespace std;

bool Asignatura::mapaInicializado = false;
static const unordered_map<string, string> *mapaCategorias;

Asignatura::Asignatura(char *cat) {
	if (!mapaInicializado) {
		initMapa();
		mapaInicializado = true;
	}
	//coger el valor del mapa
	if (mapaCategorias->find(cat) != mapaCategorias->end()) { //encuentra el valor en el mapa
		this->nombre = strdup(mapaCategorias->at(cat).data());
	} else {
		this->nombre = NULL;
	}

	this->vida = NUM_CREDITOS;
	this->vidaMax = NUM_CREDITOS;

	//PREGUNTAS-consultar BD-
	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return;
	}
	res = getPreguntasCategoria(cat, &(this->preguntas), &(this->numPreguntas));
	if (res != SQLITE_OK) {
		cout << "Error cargando las preguntas de la BD en asignatura" << endl;
		cerrarBaseDatos();
		return;
	}
	cerrarBaseDatos();

}

const int Asignatura::getNumCreditos() {
	return NUM_CREDITOS;
}

Asignatura::Asignatura(const Asignatura &other) :
		Jugador(other) {
	this->preguntas = new Pregunta[other.numPreguntas];
	this->numPreguntas = other.numPreguntas;
	for (int i = 0; i < other.numPreguntas; i++) {
		this->preguntas[i] = duplicarPregunta(&other.preguntas[i]);
	}
}

Asignatura::~Asignatura() {
	for (int i = 0; i < numPreguntas; i++) {
		freePregunta(preguntas + i);
	}
	delete[] preguntas;
}
void Asignatura::danyar() {
	vida -= DANYO;
}

void Asignatura::initMapa() {
	unordered_map<string, string> mapaCategorias2;
	mapaCategorias2["BD"] = "Base de datos";
	mapaCategorias2["MT"] = "Matematicas";
	mapaCategorias2["PR"] = "Programacion";
	mapaCategorias2["HS"] = "Historia";
	mapaCategorias2["AD"] = "ADE";
	mapaCategorias2["IN"] = "Ingles";
	mapaCategorias2["QC"] = "Computacion cuantica";
	mapaCategorias2["FI"] = "Fisica";
	mapaCategorias2["BI"] = "Biologia";
	mapaCategorias2["EA"] = "Estrcutura y Arquitectura de computadores";

	mapaCategorias = &mapaCategorias2;
}

