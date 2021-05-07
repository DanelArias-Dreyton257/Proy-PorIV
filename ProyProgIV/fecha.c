/*
 * fecha.c
 *
 *  Created on: 7 may. 2021
 *      Author: danel
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fecha.h"
/**
 * Devuelve la estructura Fecha con la fecha actual
 * @return fecha
 */
Fecha* getFechaActual() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Fecha *f = malloc(sizeof(Fecha));
	f->anyo = tm.tm_year + 1900;
	f->mes = tm.tm_mon + 1;
	f->dia = tm.tm_mday;
	f->horas = tm.tm_hour;
	f->minutos = tm.tm_min;
	f->segundos = tm.tm_sec;
	return f;
}
/**
 * Imprime la fecha pasada como parametro
 * @param fecha
 */
void imprimirFecha(Fecha f){
	printf("%02d/%02d/%d %02d:%02d:%02d",f.dia,f.mes,f.anyo,f.horas,f.minutos,f.segundos);
	fflush(stdout);
}
