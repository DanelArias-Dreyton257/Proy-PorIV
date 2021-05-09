/*
 * Jugador.h
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#ifndef JUGADOR_H_
#define JUGADOR_H_

class Jugador {
protected:
	static const int VIDA_MAX = 255;
	int vida;
	char *nombre;
public:
	Jugador(char *nombre);
	virtual ~Jugador();

	Jugador(const Jugador &other);

	char* getNombre() const;
	void setNombre(char *nombre);
	int getVida() const;
	void setVida(int vida);
	static const int getVIDA_MAX();
};

#endif /* JUGADOR_H_ */
