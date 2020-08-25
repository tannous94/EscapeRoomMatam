/*
 * order.h
 *
 *  Created on: Jun 12, 2017
 *      Author: tannous
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "mtm_ex3.h"

typedef enum {
	ORDER_SUCCESS,
	ORDER_OUT_OF_MEMORY,
	ORDER_NULL_ARG
} OrderResult;

typedef struct order_t *Order;

Order orderCreate(char* email, TechnionFaculty faculty, int room_id, char* time, int num_ppl);
Order orderCopy(Order order);
void orderDestroy(Order order);
TechnionFaculty orderGetFaculty(Order order);
int orderGetRoomId(Order order);
char* orderGetClientEmail(Order order);
int orderGetDay(Order order);
int orderGetHour(Order order);
int orderGetPpl(Order order);
OrderResult orderUpdateDay(Order order);
OrderResult orderSetHour(Order order, int hour);

#endif /* ORDER_H_ */
