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
	int record = 0;
	int puntuacion = 0;
	char *contrasena;
public:
	Usuario(char *nombre, char *contrasena, int record);
	Usuario(char *nombre, char *contrasena, int record, int puntuacion);

	virtual ~Usuario();

	Usuario(const Usuario &other);

	char* getContrasena() const;

	void danyar();
	void revitalizar();
	void print();

	static const int getVidaBase();

	int getRecord() const;
	void setRecord(int newRecord);
	int getPuntuacion() const;
	void setPuntuacion(int puntuacion);

	bool isNewRecord();
	bool checkContrasena(char *contrasena);

};

#endif /* USUARIO_H_ */
