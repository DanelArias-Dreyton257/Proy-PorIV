/*
 * pregunta.h
 *
 *  Created on: 15 mar. 2021
 *      Author: rdosp
 */

#ifndef PREGUNTA_H_
#define PREGUNTA_H_

typedef struct {
	char *pregunta[];
	char *opcion1[];
	char *opcion2[];
	char *opcion3[];
	char *opcion4[];
	int *respuesta;

} Pregunta;


#endif /* PREGUNTA_H_ */
