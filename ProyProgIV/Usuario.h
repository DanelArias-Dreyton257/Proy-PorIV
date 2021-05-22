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
private:
	static const int VIDA_BASE = 100;
	char* contrasena;
public:
	Usuario(char *nombre, char *contrasena);

	virtual ~Usuario();

	Usuario(const Usuario &other);

	char* getContrasena() const;
	static const int getVidaBase() const;
};

#endif /* USUARIO_H_ */
