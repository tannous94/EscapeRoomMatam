/*
 * mtm_escape.c
 *
 *  Created on: Jun 14, 2017
 *      Author: tannous
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#include "list.h"
#include "EscapeTechnion.h"
#include "company.h"
#include "order.h"
#include "room.h"
#include "escaper.h"
#include "mtm_ex3.h"

#define BUFFER 120

static int myAtoi(char *str) {
	if (str == NULL) {
		return -1;
	}
	int len = strlen(str);
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

static MtmErrorCode convertToMtmErr(EscapeTechnionResult result) {
	switch (result) {
	case ET_SUCCESS:
		return MTM_SUCCESS;
	case ET_OUT_OF_MEMORY:
		return MTM_OUT_OF_MEMORY;
	case ET_INVALID_PARAM:
		return MTM_INVALID_PARAMETER;
	case ET_EMAIL_ALREADY_EXISTS:
		return MTM_EMAIL_ALREADY_EXISTS;
	case ET_COMPANY_EMAIL_DOES_NOT_EXIST:
		return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
	case ET_ID_ALREADY_EXISTS:
		return MTM_ID_ALREADY_EXIST;
	case ET_ID_DOES_NOT_EXIST:
		return MTM_ID_DOES_NOT_EXIST;
	case ET_CLIENT_EMAIL_DOES_NOT_EXIST:
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	case ET_RESERVATION_EXISTS:
		return MTM_RESERVATION_EXISTS;
	case ET_CLIENT_IN_ROOM:
		return MTM_CLIENT_IN_ROOM;
	case ET_ROOM_NOT_AVAILABLE:
		return MTM_ROOM_NOT_AVAILABLE;
	case ET_NO_ROOMS_AVAILABLE:
		return MTM_NO_ROOMS_AVAILABLE;
	case ET_NULL_ARG:
		return MTM_NULL_PARAMETER;
	default:
		return -1;
	}
}

static bool isValidCommandLine(int argc, char** argv) {
	if ((argc - 1)%2 != 0 || argc > 5)
		return false;
	int countInput = 0, countOutput = 0;
	for (int i = 1; i < argc; i += 2) {
		if (strcmp("-i", argv[i]) == 0) {
			countInput++;
		}
		if (strcmp("-o", argv[i]) == 0) {
			countOutput++;
		}
	}
	if (countInput > 1 || countOutput > 1)
		return false;
	return true;
}

static FILE* getInputFile(int argc, char** argv) {
	for (int i = 1; i < argc; i += 2) {
		if (strcmp("-i", argv[i]) == 0) {
			return fopen(argv[i + 1], "r");
		}
	}
	return stdin;
}

static FILE* getOutputFile(int argc, char** argv) {
	for (int i = 1; i < argc; i += 2) {
		if (strcmp("-o", argv[i]) == 0) {
			return fopen(argv[i + 1], "w");
		}
	}
	return stdout;
}

static void executeCompanyFunctions(EscapeTechnion escape_technion, char* subCommand, char* arguments[BUFFER]) {
	assert(escape_technion != NULL && subCommand != NULL && arguments != NULL);
	EscapeTechnionResult result;
	if (!strcmp("add", subCommand)) {
		result = escapeTechnionAddCompany(escape_technion, arguments[0], myAtoi(arguments[1]));
	}
	if (!strcmp("remove", subCommand)) {
		result = escapeTechnionRemoveCompany(escape_technion, arguments[0]);
	}
	if (result != ET_SUCCESS) {
		MtmErrorCode error = convertToMtmErr(result);
		mtmPrintErrorMessage(stderr, error);
		if (error == MTM_OUT_OF_MEMORY) {
			return;
		}
	}
}

static void executeRoomFunctions(EscapeTechnion escape_technion, char* subCommand, char* arguments[BUFFER]) {
	assert(escape_technion != NULL && subCommand != NULL && arguments != NULL);
	EscapeTechnionResult result;
	if (!strcmp("add", subCommand)) {
		result = escapeTechnionAddRoom(escape_technion, arguments[0], myAtoi(arguments[1]), myAtoi(arguments[2]), myAtoi(arguments[3]), arguments[4], myAtoi(arguments[5]));
	}
	if (!strcmp("remove", subCommand)) {
		result = escapeTechnionRemoveRoom(escape_technion, myAtoi(arguments[0]), myAtoi(arguments[1]));
	}
	if (result != ET_SUCCESS) {
		MtmErrorCode error = convertToMtmErr(result);
		mtmPrintErrorMessage(stderr, error);
		if (error == MTM_OUT_OF_MEMORY) {
			return;
		}
	}
}

static void executeEscaperFunctions(EscapeTechnion escape_technion, char* subCommand, char* arguments[BUFFER]) {
	assert(escape_technion != NULL && subCommand != NULL && arguments != NULL);
	EscapeTechnionResult result;
	if (!strcmp("add", subCommand)) {
		result = escapeTechnionAddEscaper(escape_technion, arguments[0], myAtoi(arguments[1]), myAtoi(arguments[2]));
	}
	if (!strcmp("remove", subCommand)) {
		result = escapeTechnionRemoveEscaper(escape_technion, arguments[0]);
	}
	if (!strcmp("order", subCommand)) {
		result = escapeTechnionCreateOrder(escape_technion, arguments[0], myAtoi(arguments[1]), myAtoi(arguments[2]), arguments[3], myAtoi(arguments[4]));
	}
	if (result != ET_SUCCESS) {
		MtmErrorCode error = convertToMtmErr(result);
		mtmPrintErrorMessage(stderr, error);
		if (error == MTM_OUT_OF_MEMORY) {
			return;
		}
	}
}

static void executeReportFunctions(EscapeTechnion escape_technion, char* subCommand, char* arguments[BUFFER], FILE* output) {
	assert(escape_technion != NULL && subCommand != NULL && arguments != NULL);
	EscapeTechnionResult result;
	if (!strcmp("day", subCommand)) {
		result = escapeTechnionReportDay(escape_technion, output);
	}
	if (!strcmp("best", subCommand)) {
		result = escapeTechnionReportBest(escape_technion, output);
	}
	if (result != ET_SUCCESS) {
		MtmErrorCode error = convertToMtmErr(result);
		mtmPrintErrorMessage(stderr, error);
		if (error == MTM_OUT_OF_MEMORY) {
			return;
		}
	}
}

static void executeCommands(FILE* input, FILE* output) {
	char line[MAX_LEN + 1];
	EscapeTechnion escape_technion = escapeTechnionCreate();
	if (!escape_technion) {
		mtmPrintErrorMessage(stderr, MTM_OUT_OF_MEMORY);
		return;
	}
	while (fgets(line, MAX_LEN + 1, input)) {
		char* command, *subCommand;
		command = strtok(line, " \n \r \t \0");
		if (!command || command[0] == '#') {
			continue;
		}
		subCommand = strtok(NULL, " \n \r \t \0");
		char* arguments[BUFFER];
		int count = 0;
		arguments[count] = strtok(NULL, " \n \r \t \0");
		while (arguments[count++]) {
			arguments[count] = strtok(NULL, " \n \r \t \0");
		}
		if (strcmp("company", command) == 0) {
			executeCompanyFunctions(escape_technion, subCommand, arguments);
		}
		if (strcmp("room", command) == 0) {
			executeRoomFunctions(escape_technion, subCommand, arguments);
		}
		if (strcmp("escaper", command) == 0) {
			executeEscaperFunctions(escape_technion, subCommand, arguments);
		}
		if (strcmp("report", command) == 0) {
			executeReportFunctions(escape_technion, subCommand, arguments, output);
		}
	}
	escapeTechnionDestroy(escape_technion);
}

int main1(int argc, char** argv) {
	if (!isValidCommandLine(argc, argv)) {
		mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
		return 0;
	}
	FILE* input = getInputFile(argc, argv);
	if (input == NULL) {
		mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
		return 0;
	}
	FILE* output = getOutputFile(argc, argv);
	if (output == NULL) {
		mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
		return 0;
	}
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	executeCommands(input, output);
	fclose(output);
	fclose(input);
	return 0;
}
