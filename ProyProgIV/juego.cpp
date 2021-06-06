/*
 * juego.cpp
 *
 *  Created on: 23 may. 2021
 *      Author: danel
 */
#include "Jugador.h"
#include "Usuario.h"
#include <iostream>
#include "baseDatos.h"
#include "Asignatura.h"
#include <stdlib.h>
#include "pregunta.h"
#include "menu.h"

using namespace std;

Asignatura **asigs = NULL;
Usuario *u = NULL;
int numAsig = 0;
int posAsigActual = 0;

/**
 * Saca por consola la cabecera del juego mostrando el estado actual de la 2 jugadores
 */
void printEstadoJugadores(Jugador &j1, Jugador &j2) {
	cout
			<< "------------------------------------------------------------------------------"
			<< endl;

	j1.print();
	j2.print();

	cout
			<< "------------------------------------------------------------------------------"
			<< endl << endl;
}
/**
 * Inicaliza el array de asignaturas creandolas una a una segun los codigos
 */
void initAsignaturas() {

	char **array = NULL;
	getNomCategorias(&array, &numAsig);

	asigs = new Asignatura*[numAsig];

	for (int i = 0; i < numAsig; i++) {
		asigs[i] = new Asignatura(array[i]);
	}
}
/**
 * Elige aleatoriamente una posible posicion de la array de asignaturas y la guarda esta posicion en posAsigActual
 */
void selectRandAsignatura() {
	posAsigActual = rand() % numAsig;
}
/**
 * Libera la memoria de la array de asignaturas
 */
void deleteAsignaturas() {
	for (int i = 0; i < numAsig; i++) {
		delete asigs[i];
	}
	delete[] asigs;
}
/**
 * Comienza el juego y lo mantiene ejevutando hasta que el usuario pierda
 * @param nombre del usuario
 */
void jugar(char *nombre) {
	u = new Usuario(nombre);
	initAsignaturas();
	selectRandAsignatura();

	bool jugando = true;
	while (jugando) {

		//2
		limpiarConsola();
		printEstadoJugadores(*u, *asigs[posAsigActual]); //REVISAR
		//Elegir pregunta
		Pregunta *p = asigs[posAsigActual]->getPreguntaRandom();
		printPreguntaJuego(p);
		//Respuesta del usuario
		cout << "Introduce tu respuesta (a-d minusculas):" << endl;
		char res = getCharInput();
		//6->comprobar respuesta
		if (esRespuestaCorrecta(p, res - 'a') > 0) {
			//6a
			asigs[posAsigActual]->danyar();
			cout << "HAS ACERTADO LA PREGUNTA" << endl
					<< "Cada vez mas cerca de tu titulo universitario" << endl;
			pausarConsola();
		} else {
			//6b
			u->danyar();
			cout << "HAS FALLADO LA PREGUNTA!" << endl
					<< "La respuesta correcta era la " << (char) (p->res + 'A')
					<< endl << "Sufres por tu suspenso, pierdes salud mental"
					<< endl;
			pausarConsola();
		}
		//Comprobar si el usuario esta muerto
		if (u->isMuerto()) {
			//Termina el juego
			limpiarConsola();
			cout << "HAS SIDO DERROTADO" << endl
					<< "Tu fortaleza mental no es suficiente... dejas los estudios"
					<< endl << "Has conseguido: " << u->getPuntuacion()
					<< " puntos" << endl;
			actualizarRecord(u->getNombre(), u->getPuntuacion());
			pausarConsola();
			break;
		}
		//Comprobar si la asignatura ha muerto
		if (asigs[posAsigActual]->isMuerto()) {
			//Completa la asignatura y se pasa a la siguiente
			limpiarConsola();
			u->incPuntuacion();
			u->revitalizar();
			cout << "HAS SUPERADO LA ASIGNATURA" << endl
					<< "Tu salud mental ha aumentado" << endl
					<< "Tienes actualmente: " << u->getPuntuacion() << " puntos"
					<< endl;
			asigs[posAsigActual]->restaurar();
			selectRandAsignatura();
			pausarConsola();
		}
	}

	deleteAsignaturas();
}

