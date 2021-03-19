/*
 * menu.h
 *
 *  Created on: 8 mar. 2021
 *      Author: danel
 */

#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include "pregunta.h"
#include <stdlib.h>

char getCharInput();
int getIntInput();
void menuCrearPregunta();
void menuPrincipal();
void menuGestion();
void printOpciones(char *ops[], int size);
int getLIntInput(int numDigs);
char* getStringInput(int numChars);

#endif /* MENU_H_ */
