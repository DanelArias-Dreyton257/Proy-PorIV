/*
 * Usuario.h
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include "Jugador.h"

class Usuario: public Jugador {
public:
	Usuario(char *nombre):Jugador(nombre){} //TODO

	virtual ~Usuario();

	Usuario(const Usuario &other);
};

#endif /* USUARIO_H_ */
