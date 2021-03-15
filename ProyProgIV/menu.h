/*
 * menu.h
 *
 *  Created on: 8 mar. 2021
 *      Author: danel
 */
#include <stdio.h>
#include "pregunta.h"
#ifndef MENU_H_
#define MENU_H_

char getCharInput();
int getIntInput();
void menuCrearPregunta();
void menuPrincipal();
void menuGestion();
void printOpciones(char *ops[], int size);

#endif /* MENU_H_ */
