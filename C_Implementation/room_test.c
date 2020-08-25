/*
 * room_test.c
 *
 *  Created on: Jun 14, 2017
 *      Author: tannous
 */

#include "list.h"
#include "set.h"
#include "mtm_ex3.h"
#include "room.h"
#include "test_utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool testRoomCreateDestroy() {
	Room room = roomCreate("ana@hotmail.com", 15, 8, 15, "15-10", 10);
	ASSERT_TEST(room == NULL);
	room = roomCreate("ana@hotmail.com", 15, 10, 15, "15-21", 10);
	ASSERT_TEST(room == NULL);
	room = roomCreate("anahotmail.com", 15, 8, 15, "15-21", 10);
	ASSERT_TEST(room == NULL);
	room = roomCreate("ana@hotmail.com", 15, 8, 15, "15-21", 11);
	ASSERT_TEST(room == NULL);
	room = roomCreate("ana@h@otmail.com", 15, 8, 15, "15-21", 10);
	ASSERT_TEST(room == NULL);
	room = roomCreate("ana@hotmail.com", 15, 8, 15, "15-21", 10);
	ASSERT_TEST(room != NULL);
	ASSERT_TEST(roomGetOpenHour(room) == 15);
	ASSERT_TEST(roomGetCloseHour(room) == 21);
	Room copy = roomCopy(room);
	ASSERT_TEST(copy != NULL);
	ASSERT_TEST(roomGetOpenHour(copy) == 15);
	ASSERT_TEST(roomGetCloseHour(copy) == 21);
	ASSERT_TEST(roomGetBudget(copy) == 0);
	roomDestroy(copy);
	roomDestroy(room);
	return true;
}

int main2() {
	RUN_TEST(testRoomCreateDestroy);
	return 0;
}
