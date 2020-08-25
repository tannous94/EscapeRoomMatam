/*
 * order.c
 *
 *  Created on: Jun 12, 2017
 *      Author: tannous
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "order.h"
#include "mtm_ex3.h"

struct order_t {
	char* email;
	TechnionFaculty faculty;
	int room_id;
	char* time;
	int day;
	int hour;
	int num_ppl;
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

static int myAtoi(char *str, int len) {
	if (str == NULL) {
		return -1;
	}
	int i = 0;
	if (str[0] == '-') {
		i = 1;
	}
	int num = 0;
	for (; i < len - 1; i++) {
		num = num * 10 + str[i] - '0';
	}
	if (str[0] == '-') {
		num *= -1;
	}
	return num;
}

static int checkValidNum(char* time, int len) {
	for (int i = 0; i < len-1; i++) {
		if (time[i] > '9' || time[i] < '0')
			return 0;
	}
	if (myAtoi(time, len) < 0)
		return 0;
	return 1;
}

static int checkTime(char* time) {
	int len = 1;
	int i, length = strlen(time);
	for (i = 0; i < length; i++) {
		if (time[i] == '-') {
			if (!checkValidNum(time, len)) {
				return 0;
			}
			len = 1;
			break;
		}
		len++;
	}
	int save = i + 1;
	for (int j = save; j <= length; j++) {
		if (time[j] == '\0') {
			if (checkValidNum(time + save, len)) {
				if (myAtoi(time + save, len) > 23)
					return 0;
			}
			break;
		}
		len++;
	}
	return 1;
}

static int getDay(char* time) {
	int len = 1;
	int i, length = strlen(time);
	for (i = 0; i < length; i++) {
		if (time[i] == '-') {
			return myAtoi(time, len);
		}
		len++;
	}
	return -1;
}

static int getHour(char* time) {
	int len = 1;
	int i, length = strlen(time);
	for (i = 0; i < length; i++) {
		if (time[i] == '-')
			break;
	}
	int save = i + 1;
	for (int j = save; j <= length; j++) {
		if (time[j] == '\0') {
			return myAtoi(time + save, len);
		}
		len++;
	}
	return -1;
}

Order orderCreate(char* email, TechnionFaculty faculty, int room_id, char* time, int num_ppl) {
	if (!email || !checkFaculty(faculty) || room_id < 1 || num_ppl < 1 || !time)
		return NULL;
	if (!checkEmail(email) || !checkTime(time))
		return NULL;
	Order order = malloc(sizeof(*order));
	if (!order)
		return NULL;
	order->email = malloc(strlen(email) + 1);
	if (!order->email) {
		free(order);
		return NULL;
	}
	order->time = malloc(strlen(time) + 1);
	if (!order->time) {
		free(order->email);
		free(order);
		return NULL;
	}
	strcpy(order->email, email);
	strcpy(order->time, time);
	order->day = getDay(time);
	order->hour = getHour(time);
	order->faculty = faculty;
	order->num_ppl = num_ppl;
	order->room_id = room_id;
	return order;
}

Order orderCopy(Order order) {
	if (!order)
		return NULL;
	Order copyOrder = orderCreate(order->email, order->faculty, order->room_id, order->time, order->num_ppl);
	if (!copyOrder)
		return NULL;
	copyOrder->day = order->day;
	copyOrder->hour = order->hour;
	return copyOrder;
}

void orderDestroy(Order order) {
	if (!order)
		return;
	free(order->time);
	free(order->email);
	free(order);
	return;
}

TechnionFaculty orderGetFaculty(Order order) {
	if (!order)
		return UNKNOWN;
	return order->faculty;
}

int orderGetRoomId(Order order) {
	if (!order)
		return -1;
	return order->room_id;
}

char* orderGetClientEmail(Order order) {
	if (!order)
		return NULL;
	return order->email;
}

int orderGetDay(Order order) {
	if (!order)
		return -1;
	return order->day;
}

int orderGetHour(Order order) {
	if (!order)
		return -1;
	return order->hour;
}

int orderGetPpl(Order order) {
	if (!order)
		return -1;
	return order->num_ppl;
}

OrderResult orderUpdateDay(Order order) {
	if (!order)
		return ORDER_NULL_ARG;
	order->day--;
	return ORDER_SUCCESS;
}

OrderResult orderSetHour(Order order, int hour) {
	if (!order)
		return ORDER_NULL_ARG;
	order->hour = hour;
	return ORDER_SUCCESS;
}
