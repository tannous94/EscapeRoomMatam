/*
 * escaper_test.c
 *
 *  Created on: Jun 14, 2017
 *      Author: tannous
 */

#include "list.h"
#include "set.h"
#include "escaper.h"
#include "mtm_ex3.h"
#include "test_utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool testEscaperCreateDestroy() {
	Escaper escaper = escaperCreate("ana@hotmail.com", 20, 8);
	ASSERT_TEST(escaper == NULL);
	escaper = escaperCreate("ana@hotmail.com", 15, -1);
	ASSERT_TEST(escaper == NULL);
	escaper = escaperCreate("ana@@hotmail.com", 15, 8);
	ASSERT_TEST(escaper == NULL);
	escaper = escaperCreate("ana@hotmail.com", 15, 8);
	ASSERT_TEST(escaper != NULL);
	Escaper copy = escaperCopy(escaper);
	ASSERT_TEST(copy != NULL);
	ASSERT_TEST(strcmp(escaperGetEmail(escaper), "ana@hotmail.com") == 0);
	ASSERT_TEST(strcmp(escaperGetEmail(copy), "ana@hotmail.com") == 0);
	ASSERT_TEST(escaperGetFaculty(escaper) == MATERIALS_ENGINEERING);
	ASSERT_TEST(escaperGetFaculty(copy) == MATERIALS_ENGINEERING);
	ASSERT_TEST(escaperGetSkill(escaper) == 8);
	ASSERT_TEST(escaperGetSkill(copy) == 8);
	escaperDestroy(copy);
	escaperDestroy(escaper);
	return true;
}

int main3() {
	RUN_TEST(testEscaperCreateDestroy);
	return 0;
}
