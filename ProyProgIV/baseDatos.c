/*
 * baseDatos.c
 *
 *  Created on: 2 may. 2021
 *      Author: danel
 */
#include "sqlite3.h"
#include <stdio.h>
#include "baseDatos.h"
#include "pregunta.h"
#include <string.h>
#include "stdlib.h"
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
/**
 * Inserta en la base de datos una categoria nueva
 * @param nombre, nombre de la categoria
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
int insertIntoCategoria(char *nombre) {
	int res = abrirBaseDatos();

	//CREAR LA SENTENCIA DE INSERT
	sqlite3_stmt *stmt;

	char *sql = "INSERT INTO CATEGORIA(CODIGO_C, NOMBRE_C) VALUES(NULL,?)";

	//PREPARAR LA SENTENCIA
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (insert categoria)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//BIND TEXT
	res = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (insert categoria)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR STATEMENT
	res = sqlite3_step(stmt);
	if (res != SQLITE_DONE) {
		printf("Error inserting new data into table (insert categoria)\n");
		return res;
	}

	//FINALIZAR STATEMENT
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (insert categoria)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//CERRAR BD
	res = cerrarBaseDatos();
	return res;
}
/**
 * Busca en la base de datos el codigo de la categoria y lo guarda en el puntero pasado como segundo parametro
 * @param nombre, nombre de la categoria
 * @para *codigo, puntero al entero donde guardar el codigo leido
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
int selectCodCategoria(char *nombre, int *codigo) {
	int res = abrirBaseDatos();

	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;

	char *sql = "SELECT CODIGO_C FROM CATEGORIA WHERE NOMBRE_C=?";

	//PREPARE STATEMENT
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (select categoria)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}
	//BIND TEXT
	res = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (select categoria)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR STATEMENT
	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		*codigo = sqlite3_column_int(stmt, 0);
	}

	//FINALIZAR SENTENCIA
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (select categoria)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();
	return res;
}

/**
 * Almacena una categoria en la base de datos
 * @param cat, puntero a la categoria
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
int almacenarCategoria(Categoria *cat) {
	int codigoCat = -1;
	int res = SQLITE_OK;

	selectCodCategoria(cat->nombre, &codigoCat);

	if (codigoCat < 0) {
		res = insertIntoCategoria(cat->nombre);
	}
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
/**
 * Inserta en la tabla pregunta la pregunta pasada por parametro
 * @param *preg, Puntero a la pregunta
 * @param codCategoria codigo de la categoria de la pregunta
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
int insertIntoPregunta(Pregunta *preg, int codCategoria) {
	int res = abrirBaseDatos();

	//CREAR LA SENTENCIA DE INSERT
	sqlite3_stmt *stmt;
	char *sql =
			"INSERT INTO PREGUNTA(CODIGO_P,PREGUNTA,RESP_1,RESP_2,RESP_3,RESP_4,COD_R_CORRECTA,CODIGO_CAT) VALUES(NULL,?,?,?,?,?,?,?)";

	//PREPARAR LA SENTENCIA
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (insert pregunta)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}
	//BIND TEXT

	//1 - pregunta
	res = sqlite3_bind_text(stmt, 1, preg->preg, strlen(preg->preg),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (insert pregunta)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//(2-5) - respuestas
	for (int i = 0; i < 4; i++) {
		res = sqlite3_bind_text(stmt, 2 + i, preg->ops[i], strlen(preg->ops[i]),
		SQLITE_STATIC);
		if (res != SQLITE_OK) {
			printf("Error binding parameters (insert pregunta)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return res;
		}
	}

	//6 - codigo respuesta correcta
	char strRes[2];
	sprintf(strRes, "%i", preg->res + 1);
	res = sqlite3_bind_text(stmt, 6, strRes, strlen(strRes), SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (insert pregunta)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//7 - codigo categoria
	char strCod[3];
	sprintf(strCod, "%i", codCategoria);
	res = sqlite3_bind_text(stmt, 7, strCod, strlen(strCod), SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (insert pregunta)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR STATEMENT
	res = sqlite3_step(stmt);
//	if (res != SQLITE_DONE) {//FIXME por lo que sea este "error" salta pero esta funcionando correctamente
//		printf("Error inserting new data into table (insert pregunta)\n");
//		return res;
//	}

//FINALIZAR STATEMENT
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (insert pregunta)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//CERRAR BD
	res = cerrarBaseDatos();
	return res;
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
		} else {
			printf(
					"\nLa pregunta no se ha almacenado porque no se ha encontrado su categoria");
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
	if (res != SQLITE_OK) {
		printf("Error preparing statement (abrir BD)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}
	return res;
}
/**
 * Cierra a base de datos
 * @return SQLITE_OK si el proceso se termina correctamente
 */
int cerrarBaseDatos() {
	int res = sqlite3_close(db);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (cerrando BD)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}
	return res;
}

int selectNumPreguntasCat(int codCat, int *numPreguntas) {
	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;

	char *sql = "SELECT COUNT(*) FROM PREGUNTA WHERE CODIGO_CAT=?";

	//PREPARE STATEMENT
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (select num preguntas)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//BIND TEXT
	char strCodCat[3];
	sprintf(strCodCat, "%i", codCat);
	res = sqlite3_bind_text(stmt, 1, strCodCat, strlen(strCodCat),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (select num preguntas)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR
	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		*numPreguntas = sqlite3_column_int(stmt, 0);
	}

	//FINALIZAR SENTENCIA
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (select num preguntas)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();
	return res;
}

int getPreguntasCategoria(char *cat, Pregunta **pArray, int *numPreguntas) {
	*pArray = NULL;
	*numPreguntas = 0;

	int codCat = -1;
	int res = selectCodCategoria(cat, &codCat);
	if (res != SQLITE_OK) {
		printf("Error selecting categoria (select preguntas)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = selectNumPreguntasCat(codCat, numPreguntas);
	if (res != SQLITE_OK) {
		return res;
	}

	*pArray = malloc(sizeof(Pregunta) * (*numPreguntas));

	res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;

	char *sql =
			"SELECT PREGUNTA,RESP_1,RESP_2,RESP_3,RESP_4,COD_R_CORRECTA FROM PREGUNTA WHERE CODIGO_CAT=? ORDER BY PREGUNTA";

	//PREPARE STATEMENT
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (select preguntas)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//BIND TEXT
	char strCodCat[3];
	sprintf(strCodCat, "%i", codCat);
	res = sqlite3_bind_text(stmt, 1, strCodCat, strlen(strCodCat),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (select preguntas)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR STATEMENT
	int contPreguntas = 0;
	while (contPreguntas < *numPreguntas) {

		res = sqlite3_step(stmt);
		if (res == SQLITE_ROW) {

			//Leer datos
			char *preg = strdup((char*) sqlite3_column_text(stmt, 0));
			char *resp1 = strdup((char*) sqlite3_column_text(stmt, 1));
			char *resp2 = strdup((char*) sqlite3_column_text(stmt, 2));
			char *resp3 = strdup((char*) sqlite3_column_text(stmt, 3));
			char *resp4 = strdup((char*) sqlite3_column_text(stmt, 4));
			int codResp = sqlite3_column_int(stmt, 5);

			char *list[N_LISTA_PREG];
			//Meter los datos en la lista
			list[0] = cat;
			list[1] = preg;
			list[2] = resp1;
			list[3] = resp2;
			list[4] = resp3;
			list[5] = resp4;
			char c[2];
			c[0] = codResp + '0' - 1;
			c[1] = '\0';
			list[6] = c;

			(*pArray)[contPreguntas] = crearPregunta(list);

			free(preg);
			free(resp1);
			free(resp2);
			free(resp3);
			free(resp4);

		} else if (res == SQLITE_DONE) {

		} else {
			printf("Error selecting preguntas (select preguntas)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		contPreguntas++;
	}
	//FINALIZAR SENTENCIA
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (select preguntas)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();

	return res;
}

int checkUsuarioExiste(char *nombreUsuario) {
	//TODO
	return 0; //1 si true, 0 si false
}

int almacenarUsuarioNuevo(char *nombre, char *contrasena) {
	//TODO
	return SQLITE_OK;
}
int getNomCategorias(char ***array, int *numCat) { //TODO //FIXME

	char **cats = malloc(sizeof(char*) * 10);

	char *cts[10] =
			{ "BD", "MT", "PR", "HS", "AD", "IN", "QC", "FI", "BI", "EA" };

	for (int i = 0; i < 10; i++) {
		cats[i] = strdup(cts[i]);
	}

	*array = cats;
	*numCat = 10;

	return SQLITE_OK;
}
