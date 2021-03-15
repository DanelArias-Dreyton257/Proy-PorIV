/*
 * pregunta.c
 *
 *  Created on: 15 mar. 2021
 *      Author: rdosp
 */
#include <stdio.h>
#include "pregunta.h"
void printPregunta(Pregunta *p) {
	printf("%s:\n%s:\n\t %s,\n\t %s,\n\t %s,\n\t %s,\n %i",p->cat, p->preg, p->op1, p->op2,
			p->op3, p->op4, p->res);
}

Pregunta crearPregunta(char *list[]) {
	Pregunta p;

	p.cat=list[0];
	p.preg=list[1];
	p.op1=list[2];
	p.op2=list[3];
	p.op3=list[4];
	p.op4=list[5];
	p.res=2;//list[6];
	//FIXME
	return p;
}
