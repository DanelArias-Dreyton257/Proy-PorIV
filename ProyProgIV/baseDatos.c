/*
 * baseDatos.c
 *
 *  Created on: 2 may. 2021
 *      Author: danel
 */
#include "sqlite3.h"
#include <stdio.h>
#include "pregunta.h"
#include "baseDatos.h"
#define DB_FILENAME "baseDatos.sqlite"

sqlite3 *db;

int almacenarCategorias(Categoria *categorias, int numCategorias) {

	int res = SQLITE_OK;

	for (int i = 0; i < numCategorias; i++) {
		res = almacenarCategoria(categorias + i);
		if (res != SQLITE_OK) {
			break;
		}
	}
	return res;
}

int almacenarCategoria(Categoria *cat) {

	int res = abrirBaseDatos();

	//insertIntoCategoria(cat->nombre); //TODO

	if (res == SQLITE_OK) {
		for (int i = 0; i < cat->numPreguntas; i++) {
			res = almacenarPregunta(cat->preguntas + i);
			if (res != SQLITE_OK) {
				break;
			}
		}
	}
	return res;
}

int almacenarPregunta(Pregunta *preg) {

	//PRIMERO UNA SELECT PARA EL CODIGO DE LA CATEGORIA

	//CREAR LA SENTENCIA DE INSERT

	//sqlite3_stmt *stmt;

	//char *sql = "INSERT INTO PREGUNTA(CODIGO_P,PREGUNTA,RESP_1,RESP_2,RESP_3,RESP_4,COD_R_CORRECTA,COD_CAT) VALUES(NULL,?,?,?,?,?,?)";

	//PREPARAR LA SENTENCIA

	//BIND TEXT

	//EJECUTAR STATEMENT

	//FINALIZAR STATEMENT

	//CERRAR BD

	//TODO
	return -1;
}

int abrirBaseDatos() {
	int res = sqlite3_open(DB_FILENAME, &db);
	if (res != SQLITE_OK) {
		//Error al establecer la conexion
		printf("Error opening database\n");//FIXME
		return res;
	}
	printf("Database opened");//FIXME
	return res;
}

int cerrarBaseDatos() {
	int res = sqlite3_close(db);
	if (res != SQLITE_OK) {
		//Error al establecer la conexion
		printf("Error closing database\n");//FIXME
		return res;
	}
	printf("Database closed");//FIXME
	return res;
}
