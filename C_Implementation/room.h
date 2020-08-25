/*
 * room.h
 *
 *  Created on: Jun 10, 2017
 *      Author: tannous
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "mtm_ex3.h"

typedef enum {
	ROOM_SUCCESS,
	ROOM_OUT_OF_MEMORY,
	ROOM_NULL_ARG
} RoomResult;

typedef struct room_t *Room;

Room roomCreate(char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty);
Room roomCopy(Room room);
void roomDestroy(Room room);
int roomGetId(Room room);
int roomGetOpenHour(Room room);
int roomGetCloseHour(Room room);
int roomGetNumPpl(Room room);
int roomGetDifficulty(Room room);
int roomGetPrice(Room room);
int roomGetBudget(Room room);
RoomResult roomUpdateBudget(Room room, int price_to_add);

#endif /* ROOM_H_ */
