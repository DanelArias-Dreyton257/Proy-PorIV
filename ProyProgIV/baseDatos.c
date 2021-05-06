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

/**
 * Alamcena en la base de datos las categorias pasadas como parametro
 * @param categorias, puntero a una secuencia de varias categorias
 * @param numCategorias, numero de categorias
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
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

int insertIntoCategoria(char *nombre) {
	int res = abrirBaseDatos();
	//TODO
	res = cerrarBaseDatos();
	return res;
}
/**
 * Almacena una categoria en la base de datos
 * @param cat, puntero a la categoria
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
int almacenarCategoria(Categoria *cat) {

	int res = insertIntoCategoria(cat->nombre);

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

int selectCodCategoria(char *nombre, int *codigo) {
	int res = abrirBaseDatos();
	//TODO
	res = cerrarBaseDatos();
	return res;
}

int insertIntoPregunta(Pregunta *preg, codCategoria) {
	int res = abrirBaseDatos();
	//TODO
	res = cerrarBaseDatos();
	return res;

	//CREAR LA SENTENCIA DE INSERT

	//sqlite3_stmt *stmt;

	//char *sql = "INSERT INTO PREGUNTA(CODIGO_P,PREGUNTA,RESP_1,RESP_2,RESP_3,RESP_4,COD_R_CORRECTA,COD_CAT) VALUES(NULL,?,?,?,?,?,?)";

	//PREPARAR LA SENTENCIA

	//BIND TEXT

	//EJECUTAR STATEMENT

	//FINALIZAR STATEMENT

	//CERRAR BD
}
/**
 * Almacena la pregunta en la base de datos
 * @param preg, puntero a la pregunta a almacenar
 * @return SQLITE_OK si el proceso se termina correctamente
 */
int almacenarPregunta(Pregunta *preg) {

	//PRIMERO UNA SELECT PARA EL CODIGO DE LA CATEGORIA
	int codigo = -1;
	int res;
	res = selectCodCategoria(preg->cat, &codigo);

	if (res == SQLITE_OK) {
		if (codigo > -1) {
			res = insertIntoPregunta(preg, codigo);
		}
		else{
			printf("\nLa pregunta no se ha almacenado porque no se ha encontrado su categoria");
			fflush(stdout);
		}
	}

	return res;
}
/**
 * Abre la base de datos
 * @return SQLITE_OK si el proceso se termina correctamente
 */
int abrirBaseDatos() {
	int res = sqlite3_open(DB_FILENAME, &db);
	return res;
}
/**
 * Cierra a base de datos
 * @return SQLITE_OK si el proceso se termina correctamente
 */
int cerrarBaseDatos() {
	int res = sqlite3_close(db);
	return res;
}
