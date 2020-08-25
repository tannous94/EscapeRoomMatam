/*
 * escaper.h
 *
 *  Created on: Jun 10, 2017
 *      Author: tannous
 */

#ifndef ESCAPER_H_
#define ESCAPER_H_

#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "mtm_ex3.h"

typedef enum {
	ESCAPER_SUCCESS,
	ESCAPER_OUT_OF_MEMORY,
	ESCAPER_NULL_ARG
} EscaperResult;

typedef struct escaper_t *Escaper;

Escaper escaperCreate(char* email, TechnionFaculty faculty, int skill_level);
Escaper escaperCopy(Escaper escaper);
void escaperDestroy(Escaper escaper);
char* escaperGetEmail(Escaper escaper);
int escaperGetSkill(Escaper escaper);
TechnionFaculty escaperGetFaculty(Escaper escaper);

#endif /* ESCAPER_H_ */
