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
	int vidaMax;
	int vida;
	char *nombre;
public:
	Jugador();
	Jugador(char *nombre, int vidaMax);
	virtual ~Jugador();

	Jugador(const Jugador &other);

	char* getNombre() const;
	void setNombre(char *nombre);
	int getVida() const;
	void setVida(int vida);
	const int getVidaMax() const;

	virtual void danyar() = 0;
	virtual void print() = 0;

	bool isMuerto();
};

#endif /* JUGADOR_H_ */
