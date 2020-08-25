/*
 * company.c
 *
 *  Created on: Jun 9, 2017
 *      Author: tannous
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "company.h"
#include "room.h"
#include "mtm_ex3.h"

struct company_t {
	char* email;
	TechnionFaculty faculty;
	Set rooms;
};

static int checkFaculty(TechnionFaculty faculty) {
	if (faculty != CIVIL_ENGINEERING && faculty != MECHANICAL_ENGINEERING && faculty != ELECTRICAL_ENGINEERING
			&& faculty != CHEMICAL_ENGINEERING && faculty != BIOTECHNOLOGY_AND_FOOD_ENGINEERING && faculty != AEROSPACE_ENGINEERING
			&& faculty != INDUSTRIAL_ENGINEERING_AND_MANAGEMENT && faculty != MATHEMATICS && faculty != PHYSICS
			&& faculty != CHEMISTRY && faculty != BIOLOGY && faculty != ARCHITECTURE
			&& faculty != EDUCATION_IN_TECH_AND_SCIENCE && faculty != COMPUTER_SCIENCE && faculty != MEDICINE
			&& faculty != MATERIALS_ENGINEERING && faculty != HUMANITIES_AND_ARTS && faculty != BIOMEDICAL_ENGINEERING
			&& faculty != UNKNOWN)
		return 0;
	return 1;
}

static int checkEmail(char* email) {
	int len = strlen(email);
	int counter = 0;
	for (int i = 0; i < len; i++) {
		if (email[i] == '@')
			counter++;
	}
	if (counter == 1)
		return 1;
	return 0;
}

/** Copy function that copies a Room element */
static SetElement room_cpy(SetElement element) {
	if (!element)
		return NULL;
	Room copy = roomCopy((Room)element);
	if (copy == NULL)
		return NULL;
	return (SetElement)copy;
}

/** Free function that frees a Room element */
static void room_free(SetElement element) {
	if (!element)
		return;
	roomDestroy((Room)element);
	return;
}

static int room_cmp(SetElement element1, SetElement element2) {
	int id_1 = roomGetId((Room)element1);
	int id_2 = roomGetId((Room)element2);
	if (id_1 > id_2)
		return 1;
	else if (id_1 < id_2)
		return -1;
	else
		return 0;
}

static int checkRoomIdExists(Company company, Room room) {
	SET_FOREACH(Room, iter, company->rooms) {
		if (roomGetId(iter) == roomGetId(room))
			return 1;
	}
	return 0;
}

Company companyCreate(char* email, TechnionFaculty faculty) {
	if (!email || !checkFaculty(faculty))
		return NULL;
	if (!checkEmail(email))
		return NULL;
	Company company = malloc(sizeof(*company));
	if (!company)
		return NULL;
	company->email = malloc(strlen(email) + 1);
	if (!company->email) {
		free(company);
		return NULL;
	}
	strcpy(company->email, email);
	company->faculty = faculty;
	company->rooms = setCreate(room_cpy, room_free, room_cmp);
	if (!company->rooms) {
		free(company->email);
		free(company);
		return NULL;
	}
	return company;
}

Company companyCopy(Company company) {
	if (!company)
		return NULL;
	Company copyCompany = companyCreate(company->email, company->faculty);
	if (!copyCompany)
		return NULL;
	setDestroy(copyCompany->rooms);
	copyCompany->rooms = setCopy(company->rooms);
	if (!copyCompany->rooms) {
		companyDestroy(copyCompany);
		return NULL;
	}
	return copyCompany;
}

void companyDestroy(Company company) {
	if (!company)
		return;
	setDestroy(company->rooms);
	free(company->email);
	free(company);
	return;
}

char* companyGetEmail(Company company) {
	if (!company)
		return NULL;
	return company->email;
}

TechnionFaculty companyGetFaculty(Company company) {
	if (!company)
		return UNKNOWN;
	return company->faculty;
}

Set companyGetRooms(Company company) {
	if (!company)
		return NULL;
	return company->rooms;
}

CompanyResult companyAddRoom(Company company, Room room) {
	if (!company || !room)
		return COMPANY_NULL_ARG;
	if (checkRoomIdExists(company, room))
		return COMPANY_ID_ALREADY_EXISTS;
	if (setAdd(company->rooms, room) != SET_SUCCESS)
		return COMPANY_OUT_OF_MEMORY;
	return COMPANY_SUCCESS;
}

CompanyResult companyRemoveRoom(Set companies, TechnionFaculty faculty, int id) {
	if (!companies)
		return COMPANY_NULL_ARG;
	SET_FOREACH(Company, iter, companies) {
		if (companyGetFaculty(iter) == faculty) {
			Set rooms = setCopy(companyGetRooms(iter));
			SET_FOREACH(Room, iter1, rooms) {
				if (roomGetId(iter1) == id) {
					setRemove(rooms, iter1);
				}
			}
			setDestroy(rooms);
		}
	}
	return COMPANY_SUCCESS;
}

int companyGetRoomsSize(Company company) {
	if (!company)
		return -1;
	return setGetSize(company->rooms);
}
