/*
 * Asignatura.h
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#ifndef ASIGNATURA_H_
#define ASIGNATURA_H_

#include "Jugador.h"

class Asignatura: public Jugador {
private:
	static const int NUM_CREDITOS = 6;
public:
	Asignatura(char *nombre);
	virtual ~Asignatura();

	Asignatura(const Asignatura &other);
	static const int getNumCreditos() const;
};

#endif /* ASIGNATURA_H_ */
