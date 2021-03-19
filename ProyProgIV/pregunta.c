/*
 * pregunta.c
 *
 *  Created on: 15 mar. 2021
 *      Author: rdosp
 */
#include <stdio.h>
#include "pregunta.h"
#include "string.h"
#include <stdlib.h>
void printPregunta(Pregunta *p) {
	printf("%s:\n%s:\n\t %s,\n\t %s,\n\t %s,\n\t %s,\n %i->%s", p->cat, p->preg,
			*(p->ops), *(p->ops +1), *(p->ops + 2), *(p->ops + 3), p->res,
			*(p->ops + p->res));
}

Pregunta crearPregunta(char *list[]) {
	Pregunta p;

	p.cat = list[0];
	p.preg = list[1];

	char **ops = malloc(sizeof(char*) * 4);

	for (int i = 0; i < 4; i++) {
		*(ops + i) = clonar(list[2 + i]);
	}

	p.ops = ops;

	p.res = 2; //list[6];
	//FIXME
	return p;
}

void freeRespuestas(Pregunta *p){
	for (int i= 0; i<4;i++){
		free(*(p->ops + i));
	}
	free(p->ops);
}
