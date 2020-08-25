/*
 * room.c
 *
 *  Created on: Jun 10, 2017
 *      Author: tannous
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "room.h"
#include "mtm_ex3.h"

struct room_t {
	char* email;
	int id;
	int price;
	int num_ppl;
	char* working_hrs;
	int difficulty;
	int budget;
};

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

static int checkPrice(int price) {
	if (price % 4 == 0)
		return 1;
	return 0;
}

static int checkWorkingHrs(char* working_hrs) {
	for (int i = 0; i < strlen(working_hrs); i++) {
		if (i == 2)
			continue;
		if (working_hrs[i] > '9' || working_hrs[i] < '0')
			return 0;
	}
	return 1;
}

static int myAtoi(char *str, int len) {
	if (str == NULL) {
		return -1;
	}
	int i = 0;
	if (str[0] == '-') {
		i = 1;
	}
	int num = 0;
	for (; i < len; i++) {
		num = num * 10 + str[i] - '0';
	}
	if (str[0] == '-') {
		num *= -1;
	}
	return num;
}

Room roomCreate(char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty) {
	if (!email || id < 1 || price < 1 || num_ppl < 1
			|| difficulty < 1 || difficulty > 10 || !working_hrs || strlen(working_hrs) != 5)
		return NULL;
	if (!checkEmail(email) || !checkPrice(price) || !checkWorkingHrs(working_hrs))
		return NULL;
	if (myAtoi(working_hrs, 2) >= myAtoi(working_hrs+3, 2))
		return NULL;
	Room room = malloc(sizeof(*room));
	if (!room)
		return NULL;
	room->email = malloc(strlen(email) + 1);
	if (!room->email) {
		free(room);
		return NULL;
	}
	room->working_hrs = malloc(strlen(working_hrs) + 1);
	if (!room->working_hrs) {
		free(room->email);
		free(room);
		return NULL;
	}
	strcpy(room->email, email);
	strcpy(room->working_hrs, working_hrs);
	room->id = id;
	room->num_ppl = num_ppl;
	room->price = price;
	room->difficulty = difficulty;
	room->budget = 0;
	return room;
}

Room roomCopy(Room room) {
	if (!room)
		return NULL;
	Room copyRoom = roomCreate(room->email, room->id, room->price, room->num_ppl, room->working_hrs, room->difficulty);
	if (!copyRoom)
		return NULL;
	copyRoom->budget = room->budget;
	return copyRoom;
}

void roomDestroy(Room room) {
	if (!room)
		return;
	free(room->working_hrs);
	free(room->email);
	free(room);
	return;
}

int roomGetId(Room room) {
	if (!room)
		return -1;
	return room->id;
}

int roomGetOpenHour(Room room) {
	if (!room)
		return -1;
	return myAtoi(room->working_hrs, 2);
}

int roomGetCloseHour(Room room) {
	if (!room)
		return -1;
	return myAtoi(room->working_hrs + 3, 2);
}

int roomGetNumPpl(Room room) {
	if(!room)
		return -1;
	return room->num_ppl;
}

int roomGetDifficulty(Room room) {
	if (!room)
		return -1;
	return room->difficulty;
}

int roomGetPrice(Room room) {
	if (!room)
		return -1;
	return room->price;
}

int roomGetBudget(Room room) {
	if (!room)
		return -1;
	return room->budget;
}

RoomResult roomUpdateBudget(Room room, int price_to_add) {
	if (!room)
		return ROOM_NULL_ARG;
	room->budget += price_to_add;
	return ROOM_SUCCESS;
}
