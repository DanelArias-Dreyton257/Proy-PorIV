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

unordered_map<string, string> Asignatura::mapaCategorias = {
		{ "BD", "Base de datos"},
		{ "MT", "Matematicas"},
		{ "PR", "Programacion"},
		{ "HS", "Historia"},
		{ "AD", "ADE"},
		{ "IN", "Ingles"},
		{ "QC", "Computacion cuantica"},
		{ "FI", "Fisica"},
		{ "BI", "Biologia"},
		{ "IN", "Ingles"},
		{ "EA", "Estrcutura y Arquitectura de computadores"}
};

Asignatura::Asignatura(char *cat) {

	//coger el valor del mapa
	unordered_map<string, string>::const_iterator got = mapaCategorias.find(string(cat));
	if (got != mapaCategorias.end()) { //encuentra el valor en el mapa
		this->nombre = strdup(got->second.data());
	} else {
		this->nombre = (char*)"Not Found";
	}

	this->vida = NUM_CREDITOS;
	this->vidaMax = NUM_CREDITOS;

	int res = getPreguntasCategoria(cat, &(this->preguntas), &(this->numPreguntas));
	if (res != SQLITE_OK) {
		cout << "Error cargando las preguntas de la BD en asignatura" << endl;
		cerrarBaseDatos();
		return;
	}

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

void Asignatura::print() {
	cout << nombre << "(" << NUM_CREDITOS << " creditos):"<<vidaToString()<<endl;
}

void Asignatura::printPreguntas() {
	cout<<nombre<<"("<<numPreguntas<<"):"<<endl;
	for (int i =0; i<numPreguntas; i++){
		cout<<"\t";
		printPregunta(preguntas + i);
		cout<<"\n";
	}
}

