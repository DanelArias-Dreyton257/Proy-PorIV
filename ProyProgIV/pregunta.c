/*
 * pregunta.c
 *
 *  Created on: 15 mar. 2021
 *      Author: rdosp
 */
#include <stdio.h>
#include "pregunta.h"
void printPregunta(Pregunta *p) {
	printf("%s:\n\t %s,\n\t %s,\n\t %s,\n\t %s,\n %i", p->preg, p->op1, p->op2,
			p->op3, p->op4, p->res);
}
