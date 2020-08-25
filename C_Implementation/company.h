/*
 * company.h
 *
 *  Created on: Jun 9, 2017
 *      Author: tannous
 */

#ifndef COMPANY_H_
#define COMPANY_H_

#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "room.h"
#include "mtm_ex3.h"

typedef enum {
	COMPANY_SUCCESS,
	COMPANY_OUT_OF_MEMORY,
	COMPANY_ID_ALREADY_EXISTS,
	COMPANY_NULL_ARG
} CompanyResult;

typedef struct company_t *Company;

Company companyCreate(char* email, TechnionFaculty faculty);
Company companyCopy(Company company);
void companyDestroy(Company company);
char* companyGetEmail(Company company);
TechnionFaculty companyGetFaculty(Company company);
Set companyGetRooms(Company company);
CompanyResult companyAddRoom(Company company, Room room);
CompanyResult companyRemoveRoom(Set companies, TechnionFaculty faculty, int id);
int companyGetRoomsSize(Company company);

#endif /* COMPANY_H_ */
