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

/**
 * Busca en la base de datos el numero de preguntas para una categoria
 * @param codCat, codigo de la categoria
 * @para *numPreguntas, puntero al entero del numero de preguntas
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
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

/**
 * Devuelve las preguntas con toda su informacion de una categoria
 * @param cat, char* que apunta a la categoria
 * @param pArray, Pregunta** puntero a una lista de preguntas
 * @param numPreguntas, int* puntero que indica el numero de preguntas
 * @return SQLITE_OK si el proceso se termina correctamente
 */
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

/**
 * Busca en la base de datos cuantos usuarios de la tabla usuarios, tienen el nombre que se desea buscar
 * @param nombreUsuario, char* nombre del usuario a buscar en la tabla
 * @return 0 si no existe, 0< si existe (normalmente 1)
 */
int checkUsuarioExiste(char *nombreUsuario) {
	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}
	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;
	char *sql = "SELECT COUNT(*) FROM USUARIO WHERE NOMBRE_U=?";

	//PREPARAR LA SENTENCIA
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (check usuario)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//BIND TEXT
	res = sqlite3_bind_text(stmt, 1, nombreUsuario, strlen(nombreUsuario),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (check usuario)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR
	int count;
	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		count = sqlite3_column_int(stmt, 0);
	}

	//FINALIZAR STATEMENT
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (check usuario)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();

	return count; //1 si true, 0 si false
}

/**
 * Almacena un usuario nuevo en la BD
 * Para que el usuario sea nuevo, usar primero checkUsuarioExiste()
 * @param nombre, char* con el nombre del usuario
 * @param contarsena, char* con la contrasena del usuario
 * @return SQLITE_OK si el proceso se termina correctamente
 */
int almacenarUsuarioNuevo(char *nombre, char *contrasena) {
	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA DE INSERT
	sqlite3_stmt *stmt;
	char *sql =
			"INSERT INTO USUARIO(CODIGO_U,NOMBRE_U,CONTRASENA,PUNTUACION) VALUES(NULL,?,?,0)";

	//PREPARAR LA SENTENCIA
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (insert usuario)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//BIND TEXT
	res = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (insert usuario)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = sqlite3_bind_text(stmt, 2, contrasena, strlen(contrasena),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (insert usuario)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR STATEMENT
	res = sqlite3_step(stmt);

	//FINALIZAR STATEMENT
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (insert usuario)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();
	return res;
}

/**
 * Busca en la base de datos la cantidad de categorias
 * @param *numCat, indica el numero de categorias
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
int selectNumCat(int *numCat) {
	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;

	char *sql = "SELECT COUNT(*) FROM CATEGORIA";

	//PREPARE STATEMENT
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (select num categorias)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR
	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		*numCat = sqlite3_column_int(stmt, 0);
	}

	//FINALIZAR SENTENCIA
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (select num categorias)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();
	return res;
}

/**
 * Devuelve las nombre de las categorias
 * @param array, char*** puntero a una lista de todos los nombres de las categorias
 * @param numCat, int* puntero que indica el numero de categorias
 * @return SQLITE_OK si el proceso se termina correctamente
 */
int getNomCategorias(char ***array, int *numCat) {

//	char **cats = malloc(sizeof(char*) * 10);
//
//	char *cts[10] =
//			{ "BD", "MT", "PR", "HS", "AD", "IN", "QC", "FI", "BI", "EA" };
//
//	for (int i = 0; i < 10; i++) {
//		cats[i] = strdup(cts[i]);
//	}
//
//	*array = cats;
//	*numCat = 10;

	*array = NULL;
	*numCat = 0;

	int res = selectNumCat(numCat);
	if (res != SQLITE_OK) {
		return res;
	}

	*array = malloc(sizeof(char*) * (*numCat));

	res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;

	char *sql = "SELECT NOMBRE_C FROM CATEGORIA ORDER BY NOMBRE_C";

	//PREPARE STATEMENT
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (select nombre categorias)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR STATEMENT
	int contCat = 0;
	while (contCat < *numCat) {

		res = sqlite3_step(stmt);
		if (res == SQLITE_ROW) {

			//Leer datos
			char *nomCat = strdup((char*) sqlite3_column_text(stmt, 0));

			(*array)[contCat] = nomCat;

		} else if (res == SQLITE_DONE) {

		} else {
			printf("Error select (select nom categorias)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		contCat++;
	}

	//FINALIZAR SENTENCIA
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (select nom categorias)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();

	return res;

}

/**
 * Busca en la base de datos la cantidad de usuarios que hay
 * @param *numUS, indica el numero de usuarios
 * @return SQLITE_OK si el proceso ha ido correctamente
 */
int selectNumUsuarios(int *numUs) {
	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;

	char *sql = "SELECT COUNT(*) FROM USUARIO";

	//PREPARE STATEMENT
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (select num usuarios)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR
	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		*numUs = sqlite3_column_int(stmt, 0);
	}

	//FINALIZAR SENTENCIA
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (select num usuarios)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();
	return res;
}

/**
 * Devuelve los nombres y las puntuaciones de los usuarios
 * @param nombres, char*** puntero a una lista de todos los nombres de los usuarios
 * @param puntuaciones, int** puntero a una lista de puntuaciones de los usuarios
 * @param numUs, int* puntero que indica el numero de usuarios
 * @return SQLITE_OK si el proceso se termina correctamente
 */
int getRanking(char ***nombres, int **puntuaciones, int *numUs) {
//	char **noms = malloc(sizeof(char*) * 3);
//
//	noms[0] = "P3dr1T0XxX";
//	noms[1] = "ElDArrivaEsTunto";
//	noms[2] = "jugadorgenerico69";
//
//	*nombres = noms;
//
//	int *punts = malloc(sizeof(int) * 3);
//
//	punts[0] = 69;
//	punts[1] = 13;
//	punts[2] = 0;
//
//	*puntuaciones = punts;
//
//	*numUs = 3;

	*nombres = NULL;
	*puntuaciones = NULL;
	*numUs = 0;

	int res = selectNumUsuarios(numUs);
	if (res != SQLITE_OK) {
		return res;
	}

	*nombres = malloc(sizeof(char*) * (*numUs));
	*puntuaciones = malloc(sizeof(int) * (*numUs));

	res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;

	char *sql =
			"SELECT NOMBRE_U,PUNTUACION FROM USUARIO ORDER BY PUNTUACION DESC";

	//PREPARE STATEMENT
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (select ranking)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR STATEMENT
	int contUsu = 0;
	while (contUsu < *numUs) {

		res = sqlite3_step(stmt);
		if (res == SQLITE_ROW) {

			//Leer datos
			char *nombre = strdup((char*) sqlite3_column_text(stmt, 0));
			int puntuacion = sqlite3_column_int(stmt, 1);

			(*nombres)[contUsu] = nombre;
			(*puntuaciones)[contUsu] = puntuacion;

		} else if (res == SQLITE_DONE) {

		} else {
			printf("Error select (select ranking)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		contUsu++;
	}

	//FINALIZAR SENTENCIA
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (select nom ranking)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();

	return res;
}
/**
 * Comprueba si la contrasena metida es correspondiente a la almacenada
 * @param nombre, char* con el nombre del usuario
 * @param contraMetida, char* contrasena a comprobar
 * @return 0 si no existe, 0< si existe (normalmente 1)
 */
int checkContrasena(char *nombre, char *contraMetida) {

	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}
	//CREAR LA SENTENCIA
	sqlite3_stmt *stmt;
	char *sql = "SELECT COUNT(*) FROM USUARIO WHERE NOMBRE_U=? AND CONTRASENA=?";

	//PREPARAR LA SENTENCIA
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (check contrasena)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//BIND TEXT
	res = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (check contrasena)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}
	res = sqlite3_bind_text(stmt, 2, contraMetida, strlen(contraMetida),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (check contrasena)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}
	//EJECUTAR
	int count;
	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		count = sqlite3_column_int(stmt, 0);
	}

	//FINALIZAR STATEMENT
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (check contrasena)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();

	return count; //1 si true, 0 si false
}

int getRecordActual(char *nombre) {
	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA DE INSERT
	sqlite3_stmt *stmt;
	char *sql = "SELECT PUNTUACION FROM USUARIO WHERE NOMBRE_U=?";

	//PREPARAR LA SENTENCIA
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (get record)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}
	//BIND TEXT
	res = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (get record)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	int record;
	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		record = sqlite3_column_int(stmt, 0);
	}

	//FINALIZAR STATEMENT
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (actualizar record)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();
	return record;
}

/**
 * Actualiza la puntuacion record del usuario almacenada en la base de datos
 * @param nombre, char* con el nombre del usuario
 * @param puntuacion, nueva puntuacion del usuario
 * @return SQLITE_OK si el proceso se termina correctamente
 */
int actualizarRecord(char *nombre, int puntuacion) {

	if(getRecordActual(nombre)>puntuacion){
		return SQLITE_OK;
	}

	int res = abrirBaseDatos();
	if (res != SQLITE_OK) {
		return res;
	}

	//CREAR LA SENTENCIA DE INSERT
	sqlite3_stmt *stmt;
	char *sql = "UPDATE USUARIO SET PUNTUACION=? WHERE NOMBRE_U=?";

	//PREPARAR LA SENTENCIA
	res = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (res != SQLITE_OK) {
		printf("Error preparing statement (actualizar record)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//BIND TEXT
	char strPunt[10];
	sprintf(strPunt, "%i", puntuacion);
	res = sqlite3_bind_text(stmt, 1, strPunt, strlen(strPunt),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (actualizar record)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = sqlite3_bind_text(stmt, 2, nombre, strlen(nombre),
	SQLITE_STATIC);
	if (res != SQLITE_OK) {
		printf("Error binding parameters (actualizar record)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	//EJECUTAR STATEMENT
	res = sqlite3_step(stmt);

	//FINALIZAR STATEMENT
	res = sqlite3_finalize(stmt);
	if (res != SQLITE_OK) {
		printf("Error finalizing statement (actualizar record)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return res;
	}

	res = cerrarBaseDatos();
	return res;
}
