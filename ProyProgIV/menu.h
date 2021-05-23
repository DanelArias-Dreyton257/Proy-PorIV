/*
 * menu.h
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */

#ifndef MENU_H_
#define MENU_H_

#ifdef __cplusplus
extern "C" {
#endif

char getCharInput();
int getIntInput();
int getLIntInput(int numDigs);
char* getStringInput(int numChars);

void menuCrearPregunta();
void menuPrincipal();
void menuGestion();
void menuModPregunta();
void menuBorrarPregunta();
void menuJugar();

void preguntarProvisional();

void verPreguntas();
void volcarFicheroABD();

void printOpciones(char *ops[], int size);

void limpiarConsola();
void pausarConsola();

#ifdef __cplusplus
}
#endif


#endif /* MENU_H_ */
