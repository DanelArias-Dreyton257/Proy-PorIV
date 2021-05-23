/*
 * fecha.h
 *
 *  Created on: 7 may. 2021
 *      Author: danel
 */

#ifndef FECHA_H_
#define FECHA_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	int dia;
	int mes;
	int anyo;
	int horas;
	int minutos;
	int segundos;
} Fecha;

Fecha* getFechaActual();
void imprimirFecha(Fecha f);

#ifdef __cplusplus
}
#endif

#endif /* FECHA_H_ */
