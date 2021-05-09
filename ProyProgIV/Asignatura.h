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
public:
	Asignatura(char *nombre):Jugador(nombre){}//TODO
	virtual ~Asignatura();

	Asignatura(const Asignatura &other);
};

#endif /* ASIGNATURA_H_ */
