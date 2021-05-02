/*
 * baseDatos.h
 *
 *  Created on: 2 may. 2021
 *      Author: danel
 */

#ifndef BASEDATOS_H_
#define BASEDATOS_H_

#include "pregunta.h"

int almacenarCategorias(Categoria *categorias, int numCategorias);
int almacenarCategoria(Categoria *cat);
int almacenarPregunta(Pregunta* preg);
int abrirBaseDatos();

#endif /* BASEDATOS_H_ */
