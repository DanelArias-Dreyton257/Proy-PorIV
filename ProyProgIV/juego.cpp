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

void printEstadoJugadores(Jugador &j1, Jugador &j2) {
	cout << "------------------------------------------------------------------------------" << endl;
	j1.print();
	j2.print();
	cout << "------------------------------------------------------------------------------" << endl<<endl;
}

void initAsignaturas() {

	char **array = NULL;
	getNomCategorias(&array, &numAsig);

	asigs = new Asignatura*[numAsig];

	for (int i = 0; i < numAsig; i++) {
		asigs[i] = new Asignatura(array[i]);
	}
}

void selectRandAsignatura() {
	posAsigActual = rand() % numAsig;
}

void deleteAsignaturas() {
	for (int i = 0; i < numAsig; i++) {
		delete asigs[i];
	}
	delete[] asigs;
}

void jugar(char *nombre) {
	u = new Usuario(nombre);
	initAsignaturas();
	selectRandAsignatura();

	//1

	bool jugando = true;
	while (jugando) {

		//2
		limpiarConsola();
		printEstadoJugadores(*u, *asigs[posAsigActual]); //REVISAR
		//3
		Pregunta *p = asigs[posAsigActual]->getPreguntaRandom();
		//4
		printPreguntaJuego(p);
		//5
		cout << "Introduce tu respuesta (a-d minusculas):" << endl;
		char res = getCharInput();
		//6
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
					<< "La respuesta correcta era la " << (char)(p->res + 'A') << endl
					<< "Sufres por tu suspenso, pierdes salud mental" << endl;
			pausarConsola();
		}
		//7
		if (u->isMuerto()) {
			limpiarConsola();
			cout << "HAS SIDO DERROTADO" << endl
					<< "Tu fortaleza mental no es suficiente... dejas los estudios"
					<< endl << "Has conseguido: " << u->getPuntuacion()
					<< " puntos" << endl;
			actualizarRecord(u->getNombre(), u->getPuntuacion());
			pausarConsola();
			break;
		}
		//8
		if (asigs[posAsigActual]->isMuerto()) {
			//8a
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

