/*
 * pregunta.h
 *
 *  Created on: 15 mar. 2021
 *      Author: rdosp
 */

#ifndef PREGUNTA_H_
#define PREGUNTA_H_

typedef struct {
	char *cat;
	char *preg;
	char *op1;
	char *op2;
	char *op3;
	char *op4;
	int res;

} Pregunta;
void printPregunta(Pregunta *p);
Pregunta crearPregunta(char *list[]);
#endif /* PREGUNTA_H_ */
