/*
 * Asignatura.h
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#ifndef ASIGNATURA_H_
#define ASIGNATURA_H_

#include "Jugador.h"
#include <unordered_map>
#include <string>
using namespace std;

class Asignatura: public Jugador {
private:
	static const int NUM_CREDITOS = 6;
	static const int DANYO = 2;
	static void initMapa();
	static bool mapaInicializado;
public:
	Asignatura(char *cat);
	virtual ~Asignatura();

	Asignatura(const Asignatura &other);
	static const int getNumCreditos();

	void danyar();

};

#endif /* ASIGNATURA_H_ */
