/*
 * company_test.c
 *
 *  Created on: Jun 14, 2017
 *      Author: tannous
 */

#include "list.h"
#include "set.h"
#include "company.h"
#include "room.h"
#include "mtm_ex3.h"
#include "test_utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool testCompanyCreateDestroy() {
	Company company = companyCreate("ana@h@otmail.com", 15);
	ASSERT_TEST(company == NULL);
	company = companyCreate("ana@hotmail.com", 15);
	ASSERT_TEST(company != NULL);
	Room room = roomCreate("ana1@hotmail.com", 12, 16, 6, "15-20", 2);
	ASSERT_TEST(room != NULL);
	Room room1 = roomCreate("ana1@hotmail.com", 12, 8, 6, "15-20", 2);
	ASSERT_TEST(room1 != NULL);
	Room room2 = roomCreate("ana1@hotmail.com", 14, 8, 6, "15-20", 2);
	ASSERT_TEST(room2 != NULL);
	ASSERT_TEST(strcmp(companyGetEmail(company), "ana@hotmail.com") == 0);
	ASSERT_TEST(roomGetId(room) == 12);
	ASSERT_TEST(roomGetId(room1) == 12);
	ASSERT_TEST(companyGetRoomsSize(company) == 0);
	ASSERT_TEST(companyAddRoom(company, room) == COMPANY_SUCCESS);
	ASSERT_TEST(companyAddRoom(company, room1) == COMPANY_ID_ALREADY_EXISTS);
	ASSERT_TEST(companyGetRoomsSize(company) == 1);
	ASSERT_TEST(roomGetOpenHour(setGetFirst(companyGetRooms(company))) == 15);
	ASSERT_TEST(companyAddRoom(company, room2) == COMPANY_SUCCESS);
	ASSERT_TEST(companyGetRoomsSize(company) == 2);
	Company copy = companyCopy(company);
	ASSERT_TEST(roomGetOpenHour(setGetFirst(companyGetRooms(copy))) == 15);
	ASSERT_TEST(roomGetId(setGetFirst(companyGetRooms(copy))) == 12);
	ASSERT_TEST(companyGetRoomsSize(copy) == 2);
	companyDestroy(copy);
	roomDestroy(room2);
	roomDestroy(room1);
	roomDestroy(room);
	companyDestroy(company);
	return true;
}

int main() {
	RUN_TEST(testCompanyCreateDestroy);
	return 0;
}
