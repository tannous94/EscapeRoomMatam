/*
 * EscapeTechnion.h
 *
 *  Created on: Jun 10, 2017
 *      Author: tannous
 */

#ifndef ESCAPETECHNION_H_
#define ESCAPETECHNION_H_

#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "escaper.h"
#include "room.h"
#include "order.h"
#include "company.h"
#include "mtm_ex3.h"

typedef enum {
	ET_SUCCESS,
	ET_OUT_OF_MEMORY,
	ET_INVALID_PARAM,
	ET_EMAIL_ALREADY_EXISTS,
	ET_COMPANY_EMAIL_DOES_NOT_EXIST,
	ET_ID_ALREADY_EXISTS,
	ET_ID_DOES_NOT_EXIST,
	ET_CLIENT_EMAIL_DOES_NOT_EXIST,
	ET_RESERVATION_EXISTS,
	ET_CLIENT_IN_ROOM,
	ET_ROOM_NOT_AVAILABLE,
	ET_NO_ROOMS_AVAILABLE,
	ET_NULL_ARG
} EscapeTechnionResult;

typedef struct escapetechnion_t *EscapeTechnion;

EscapeTechnion escapeTechnionCreate();
void escapeTechnionDestroy(EscapeTechnion escapeTechnion);
EscapeTechnionResult escapeTechnionAddCompany(EscapeTechnion escapeTechnion, char* email, TechnionFaculty faculty);
EscapeTechnionResult escapeTechnionRemoveCompany(EscapeTechnion escapeTechnion, char* email);
EscapeTechnionResult escapeTechnionAddRoom(EscapeTechnion escapeTechnion, char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty);
EscapeTechnionResult escapeTechnionRemoveRoom(EscapeTechnion escapeTechnion, TechnionFaculty faculty, int id);
EscapeTechnionResult escapeTechnionAddEscaper(EscapeTechnion escapeTechnion, char* email, TechnionFaculty faculty, int skill_level);
EscapeTechnionResult escapeTechnionRemoveEscaper(EscapeTechnion escapeTechnion, char* email);
EscapeTechnionResult escapeTechnionCreateOrder(EscapeTechnion escapeTechnion, char* email, TechnionFaculty faculty, int id, char* time, int num_ppl);
EscapeTechnionResult escapeTechnionRecommendRoom(EscapeTechnion escapeTechnion, char* email, int num_ppl);
EscapeTechnionResult escapeTechnionReportDay(EscapeTechnion escapeTechnion, FILE* output);
EscapeTechnionResult escapeTechnionReportBest(EscapeTechnion escapeTechnion, FILE* output);

#endif /* ESCAPETECHNION_H_ */
