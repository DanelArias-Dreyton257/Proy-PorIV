/*
 * Asignatura.h
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#ifndef ASIGNATURA_H_
#define ASIGNATURA_H_

#include "Jugador.h"
#include "pregunta.h"
#include <unordered_map>
#include <string>
using namespace std;

class Asignatura: public Jugador {
private:
	static const int NUM_CREDITOS = 6;
	static const int DANYO = 2;
	static unordered_map<string, string> mapaCategorias;
	Pregunta *preguntas = NULL;
	int numPreguntas = 0;
public:
	Asignatura(char *cat);
	virtual ~Asignatura();

	Asignatura(const Asignatura &other);
	static const int getNumCreditos();

	void danyar();
	void print();

};

#endif /* ASIGNATURA_H_ */
