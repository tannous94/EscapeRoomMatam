/*
 * order_test.c
 *
 *  Created on: Jun 14, 2017
 *      Author: tannous
 */

#include "list.h"
#include "set.h"
#include "order.h"
#include "mtm_ex3.h"
#include "test_utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool testOrderCreateDestroy() {
	Order order = orderCreate("ana@h@otmail.com", 15, 8, "10-19", 15);
	ASSERT_TEST(order == NULL);
	order = orderCreate("ana@hotmail.com", 20, 8, "10-19", 15);
	ASSERT_TEST(order == NULL);
	order = orderCreate("ana@hotmail.com", 15, 0, "10-19", 15);
	ASSERT_TEST(order == NULL);
	order = orderCreate("ana@hotmail.com", 15, 8, "10-25", 15);
	ASSERT_TEST(order == NULL);
	Order order1 = orderCreate("ana@hotmail.com", 15, 8, "0-19", 15);
	ASSERT_TEST(order1 != NULL);
	Order order2 = orderCreate("ana@hotmail.com", 15, 8, "125-19", 15);
	ASSERT_TEST(order2 != NULL);
	order = orderCreate("ana@hotmail.com", 15, 8, "10-19", 15);
	ASSERT_TEST(order != NULL);
	ASSERT_TEST(orderGetDay(order) == 10);
	ASSERT_TEST(orderGetDay(order1) == 0);
	ASSERT_TEST(orderGetDay(order2) == 125);
	ASSERT_TEST(orderGetHour(order2) == 19);
	ASSERT_TEST(orderGetHour(order) == 19);
	ASSERT_TEST(strcmp(orderGetClientEmail(order), "ana@hotmail.com") == 0);
	ASSERT_TEST(orderUpdateDay(order) == ORDER_SUCCESS);
	ASSERT_TEST(orderGetDay(order) == 9);
	ASSERT_TEST(orderSetHour(order, 28) == ORDER_SUCCESS);
	ASSERT_TEST(orderGetHour(order) == 28);
	Order copy = orderCopy(order);
	ASSERT_TEST(copy != NULL);
	ASSERT_TEST(orderGetDay(copy) == 9);
	ASSERT_TEST(strcmp(orderGetClientEmail(copy), "ana@hotmail.com") == 0);
	orderDestroy(copy);
	orderDestroy(order);
	orderDestroy(order2);
	orderDestroy(order1);
	return true;
}

int main4() {
	RUN_TEST(testOrderCreateDestroy);
	return 0;
}
