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
	static const int INC_RECU = 10;
	static const int DANYO = 20;
	char* contrasena;
public:
	Usuario(char *nombre, char *contrasena);

	virtual ~Usuario();

	Usuario(const Usuario &other);

	char* getContrasena() const;

	void danyar();
	void revitalizar();
	void print();


	static const int getVidaBase();
};

#endif /* USUARIO_H_ */
