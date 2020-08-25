/*
 * EscapeTechnion.c
 *
 *  Created on: Jun 10, 2017
 *      Author: tannous
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include "EscapeTechnion.h"
#include "company.h"
#include "order.h"
#include "room.h"
#include "escaper.h"
#include "mtm_ex3.h"

#define FAC_NUM 19
#define FAC_TOTAL 18

struct escapetechnion_t {
	int time;
	Set companies;
	Set escapers;
	List orders;
};

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

static void reverse(char* s) {
    int i, j;
    char c;
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void myItoa(int day, int hour, char* time) {
	int i = 0;
    do {
        time[i++] = day % 10 + '0';
    } while ((day /= 10) > 0);
    time[i++] = '-';
    do {
        time[i++] = hour % 10 + '0';
    } while ((hour /= 10) > 0);
    time[i] = '\0';
    reverse(time);
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

static int checkPrice(int price) {
	if (price < 1)
		return 0;
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

static SetElement company_cpy(SetElement element) {
	if (!element)
		return NULL;
	Company copy = companyCopy((Company)element);
	if (copy == NULL)
		return NULL;
	return (SetElement)copy;
}

static void company_free(SetElement element) {
	if (!element)
		return;
	companyDestroy((Company)element);
	return;
}

static int company_cmp(SetElement element1, SetElement element2) {
	return strcmp(companyGetEmail((Company)element1), companyGetEmail((Company)element2));
}

static SetElement escaper_cpy(SetElement element) {
	if (!element)
		return NULL;
	Escaper copy = escaperCopy((Escaper)element);
	if (copy == NULL)
		return NULL;
	return (SetElement)copy;
}

static void escaper_free(SetElement element) {
	if (!element)
		return;
	escaperDestroy((Escaper)element);
	return;
}

static int escaper_cmp(SetElement element1, SetElement element2) {
	return strcmp(escaperGetEmail((Escaper)element1), escaperGetEmail((Escaper)element2));
}

static ListElement order_cpy(ListElement element) {
	if (!element)
		return NULL;
	Order copy = orderCopy((Order)element);
	if (copy == NULL)
		return NULL;
	return (ListElement)copy;
}

static void order_free(ListElement element) {
	if (!element)
		return;
	orderDestroy((Order)element);
	return;
}

static int companyContains(EscapeTechnion escapeTechnion, char* email) {
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (strcmp(companyGetEmail(iter), email) == 0)
			return 1;
	}
	return 0;
}

static int escapersContains(EscapeTechnion escapeTechnion, char* email) {
	SET_FOREACH(Escaper, iter, escapeTechnion->escapers) {
		if (strcmp(escaperGetEmail(iter), email) == 0)
			return 1;
	}
	return 0;
}

static int emailFound(EscapeTechnion escapeTechnion, char* email) {
	SET_FOREACH(Escaper, iter, escapeTechnion->escapers) {
		if (strcmp(escaperGetEmail(iter), email) == 0)
			return 1;
	}
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (strcmp(companyGetEmail(iter), email) == 0)
			return 1;
	}
	return 0;
}

static Company companyGet(EscapeTechnion escapeTechnion, char* email) {
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (strcmp(companyGetEmail(iter), email) == 0)
			return iter;
	}
	return NULL;
}

static Escaper escaperGet(EscapeTechnion escapeTechnion, char* email) {
	SET_FOREACH(Escaper, iter, escapeTechnion->escapers) {
		if (strcmp(escaperGetEmail(iter), email) == 0)
			return iter;
	}
	return NULL;
}

static int checkRoomId(EscapeTechnion escapeTechnion, char* email, int id) {
	TechnionFaculty save = UNKNOWN;
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (strcmp(companyGetEmail(iter), email) == 0)
			save = companyGetFaculty(iter);
	}
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (companyGetFaculty(iter) == save) {
			SET_FOREACH(Room, iter1, companyGetRooms(iter)) {
				if (roomGetId(iter1) == id)
					return 1;
			}
		}
	}
	return 0;
}

static int checkIdInFaculty(EscapeTechnion escapeTechnion, TechnionFaculty faculty, int id) {
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (companyGetFaculty(iter) == faculty) {
			SET_FOREACH(Room, iter1, companyGetRooms(iter)) {
				if (roomGetId(iter1) == id)
					return 1;
			}
		}
	}
	return 0;
}

static int checkOrderInCompany(EscapeTechnion escapeTechnion, char* email) {
	Company company = companyCopy(companyGet(escapeTechnion, email));
	if (!company)
		return -1;
	TechnionFaculty faculty = companyGetFaculty(company);
	LIST_FOREACH(Order, iter, escapeTechnion->orders) {
		if (faculty == orderGetFaculty(iter))
			return 1;
	}
	companyDestroy(company);
	return 0;
}

static int checkReservation(EscapeTechnion escapeTechnion, TechnionFaculty faculty, int id) {
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (companyGetFaculty(iter) == faculty) {
			SET_FOREACH(Room, iter1, companyGetRooms(iter)) {
				if (roomGetId(iter1) == id) {
					LIST_FOREACH(Order, iter2, escapeTechnion->orders) {
						if (id == orderGetRoomId(iter2)) {
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

static int checkValidNum(char* time, int len) {
	for (int i = 0; i < len; i++) {
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

static int checkOrderExists(EscapeTechnion escapeTechnion, char* email, int day, int hour) {
	LIST_FOREACH(Order, iter, escapeTechnion->orders) {
		if (strcmp(orderGetClientEmail(iter), email) == 0) {
			if (day == orderGetDay(iter)) {
				if (hour == orderGetHour(iter)) {
					return 1;
				}
			}
		}
	}
	return 0;
}

static int checkRoomAvailable(EscapeTechnion escapeTechnion, TechnionFaculty faculty, int id, int day, int hour) {
	LIST_FOREACH(Order, iter, escapeTechnion->orders) {
		if (orderGetFaculty(iter) == faculty && orderGetRoomId(iter) == id) {
			if (orderGetDay(iter) == day && orderGetHour(iter) == hour) {
				return 0;
			}
		}
	}
	return 1;
}

static int checkRoomTimes(EscapeTechnion escapeTechnion, TechnionFaculty faculty, int id, int hour) {
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (companyGetFaculty(iter) == faculty) {
			SET_FOREACH(Room, iter1, companyGetRooms(iter)) {
				if (roomGetId(iter1) == id) {
					if (roomGetOpenHour(iter1) >= hour && roomGetCloseHour(iter1) < hour) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

static int checkRoomsFound(EscapeTechnion escapeTechnion) {
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		if (companyGetRoomsSize(iter) > 0)
			return 1;
	}
	return 0;
}

static int getEqResult(EscapeTechnion escapeTechnion, Room room, int num_ppl, char* email) {
	int result;
	SET_FOREACH(Escaper, iter, escapeTechnion->escapers) {
		if (strcmp(escaperGetEmail(iter), email) == 0) {
			result = (roomGetNumPpl(room) - num_ppl)*(roomGetNumPpl(room) - num_ppl);
			result += (roomGetDifficulty(room) - escaperGetSkill(iter))*(roomGetDifficulty(room) - escaperGetSkill(iter));
		}
	}
	return result;
}

static TechnionFaculty escaperFaculty(EscapeTechnion escapeTechnion, char* email) {
	SET_FOREACH(Escaper, iter, escapeTechnion->escapers) {
		if (strcmp(escaperGetEmail(iter), email) == 0) {
			return escaperGetFaculty(iter);
		}
	}
	return UNKNOWN;
}

static int abs_faculty(int n) {
	if (n < 0)
		return -n;
	return n;
}

static int cmpFaculty(TechnionFaculty escaper_faculty, TechnionFaculty saved_faculty, TechnionFaculty current_faculty) {
	int a = abs_faculty(escaper_faculty - saved_faculty);
	int b = abs_faculty(escaper_faculty - current_faculty);
	if (a > b)
		return 1;
	else if (b > a)
		return -1;
	else
		return 0;
}

static int getClientSkill(EscapeTechnion escapeTechnion, Order order) {
	if (!order)
		return -1;
	SET_FOREACH(Escaper, iter, escapeTechnion->escapers) {
		if (strcmp(escaperGetEmail(iter), orderGetClientEmail(order)) == 0) {
			return escaperGetSkill(iter);
		}
	}
	return -1;
}

static int indexOfMax(int* arr, int len) {
	int i, i_max = 0;
	for (i = 1; i < len; i++) {
		if (arr[i] >= arr[i_max]) {
			if (arr[i] > arr[i_max])
				i_max = i;
			if (arr[i] == arr[i_max])
				if (i < i_max)
					i_max = i;
		}
	}
	return i_max;
}

static void updateTotalPrice(EscapeTechnion escapeTechnion) {
	int total_price;
	LIST_FOREACH(Order, iter, escapeTechnion->orders) {
		if (orderGetDay(iter) == 0) {
			SET_FOREACH(Company, iter1, escapeTechnion->companies) {
				SET_FOREACH(Room, iter2, companyGetRooms(iter1)) {
					if (companyGetFaculty(iter1) == orderGetFaculty(iter) && roomGetId(iter2) == orderGetRoomId(iter)) {
						if (escaperGetFaculty(escaperGet(escapeTechnion, orderGetClientEmail(iter))) == companyGetFaculty(iter1)) {
							total_price = (roomGetPrice(iter2) * orderGetPpl(iter) * 3) / 4;
						} else {
							total_price = roomGetPrice(iter2) * orderGetPpl(iter);
						}
						roomUpdateBudget(iter2, total_price);
					}
				}
			}
		}
	}
}

static void updateOrderHour(EscapeTechnion escapeTechnion, int save_fac_id, int save_room_id) {
	LIST_FOREACH(Order, iter, escapeTechnion->orders) {
		if (orderGetFaculty(iter) == save_fac_id && orderGetRoomId(iter) == save_room_id) {
			orderSetHour(iter, 25);
		}
	}
}

static void printOrders(EscapeTechnion escapeTechnion, int* faculty_id, int* room_id, int counter, FILE* output) {
	for (int i = 0;i < counter; i++) {
		LIST_FOREACH(Order, iter, escapeTechnion->orders) {
			if (faculty_id[i] == orderGetFaculty(iter) && room_id[i] == orderGetRoomId(iter)) {
				Company company;
				Room room;
				SET_FOREACH(Company, iter1, escapeTechnion->companies) {
					SET_FOREACH(Room, iter2, companyGetRooms(iter1)) {
						if (faculty_id[i] == companyGetFaculty(iter1) && room_id[i] == roomGetId(iter2)) {
							company = companyCopy(iter1);
							room = roomCopy(iter2);
						}
					}
				}
				int total_price;
				if (escaperGetFaculty(escaperGet(escapeTechnion, orderGetClientEmail(iter))) == companyGetFaculty(company)) {
					total_price = (roomGetPrice(room) * orderGetPpl(iter) * 3) / 4;
				} else {
					total_price = roomGetPrice(room) * orderGetPpl(iter);
				}
				mtmPrintOrder(output, orderGetClientEmail(iter), getClientSkill(escapeTechnion, iter), escaperFaculty(escapeTechnion,
												orderGetClientEmail(iter)), companyGetEmail(company), orderGetFaculty(iter), roomGetId(room), orderGetHour(iter), roomGetDifficulty(room), orderGetPpl(iter), total_price);
				listRemoveCurrent(escapeTechnion->orders);
				roomDestroy(room);
				companyDestroy(company);
			}
		}
	}
}

EscapeTechnion escapeTechnionCreate() {
	EscapeTechnion escapeTechnion = malloc(sizeof(*escapeTechnion));
	if (!escapeTechnion)
		return NULL;
	escapeTechnion->companies = setCreate(company_cpy, company_free, company_cmp);
	if (!escapeTechnion->companies) {
		free(escapeTechnion);
		return NULL;
	}
	escapeTechnion->escapers = setCreate(escaper_cpy, escaper_free, escaper_cmp);
	if (!escapeTechnion->escapers) {
		setDestroy(escapeTechnion->companies);
		free(escapeTechnion);
		return NULL;
	}
	escapeTechnion->orders = listCreate(order_cpy, order_free);
	if (!escapeTechnion->orders) {
		setDestroy(escapeTechnion->escapers);
		setDestroy(escapeTechnion->companies);
		free(escapeTechnion);
		return NULL;
	}
	escapeTechnion->time = 0;
	return escapeTechnion;
}

void escapeTechnionDestroy(EscapeTechnion escapeTechnion) {
	if (!escapeTechnion)
		return;
	listDestroy(escapeTechnion->orders);
	setDestroy(escapeTechnion->escapers);
	setDestroy(escapeTechnion->companies);
	free(escapeTechnion);
	return;
}

EscapeTechnionResult escapeTechnionAddCompany(EscapeTechnion escapeTechnion, char* email, TechnionFaculty faculty) {
	if (!escapeTechnion || !email)
		return ET_NULL_ARG;
	if (!checkEmail(email) || !checkFaculty(faculty))
		return ET_INVALID_PARAM;
	if (emailFound(escapeTechnion, email))
		return ET_EMAIL_ALREADY_EXISTS;
	Company company = companyCreate(email, faculty);
	if (!company)
		return ET_OUT_OF_MEMORY;
	setAdd(escapeTechnion->companies, company);
	companyDestroy(company);
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionRemoveCompany(EscapeTechnion escapeTechnion, char* email) {
	if (!escapeTechnion || !email)
		return ET_NULL_ARG;
	if (!checkEmail(email))
		return ET_INVALID_PARAM;
	if (!companyContains(escapeTechnion, email))
		return ET_COMPANY_EMAIL_DOES_NOT_EXIST;
	if (checkOrderInCompany(escapeTechnion, email))
		return ET_RESERVATION_EXISTS;
	setRemove(escapeTechnion->companies, companyGet(escapeTechnion, email));
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionAddRoom(EscapeTechnion escapeTechnion, char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty) {
	if (!escapeTechnion || !email || !working_hrs)
		return ET_NULL_ARG;
	if (!checkEmail(email) || id < 1 || num_ppl < 1 || !checkPrice(price) || difficulty < 1
			|| difficulty > 10 || strlen(working_hrs) != 5)
		return ET_INVALID_PARAM;
	if (!checkWorkingHrs(working_hrs))
		return ET_INVALID_PARAM;
	if (myAtoi(working_hrs, 2) >= myAtoi(working_hrs+3, 2))
		return ET_INVALID_PARAM;
	if (!companyContains(escapeTechnion, email))
		return ET_COMPANY_EMAIL_DOES_NOT_EXIST;
	if (checkRoomId(escapeTechnion, email, id))
		return ET_ID_ALREADY_EXISTS;
	Room room = roomCreate(email, id, price, num_ppl, working_hrs, difficulty);
	if (!room)
		return ET_OUT_OF_MEMORY;
	companyAddRoom(companyGet(escapeTechnion, email), room);
	roomDestroy(room);
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionRemoveRoom(EscapeTechnion escapeTechnion, TechnionFaculty faculty, int id) {
	if (!escapeTechnion)
		return ET_NULL_ARG;
	if (!checkFaculty(faculty) || id < 1)
		return ET_INVALID_PARAM;
	if (!checkIdInFaculty(escapeTechnion, faculty, id))
		return ET_ID_DOES_NOT_EXIST;
	if (checkReservation(escapeTechnion, faculty, id))
		return ET_RESERVATION_EXISTS;
	companyRemoveRoom(escapeTechnion->companies, faculty, id);
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionAddEscaper(EscapeTechnion escapeTechnion, char* email, TechnionFaculty faculty, int skill_level) {
	if (!escapeTechnion || !email)
		return ET_NULL_ARG;
	if (!checkEmail(email) || !checkFaculty(faculty) || skill_level < 1 || skill_level > 10)
		return ET_INVALID_PARAM;
	if (emailFound(escapeTechnion, email))
		return ET_EMAIL_ALREADY_EXISTS;
	Escaper escaper = escaperCreate(email, faculty, skill_level);
	if (!escaper)
		return ET_OUT_OF_MEMORY;
	setAdd(escapeTechnion->escapers, escaper);
	escaperDestroy(escaper);
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionRemoveEscaper(EscapeTechnion escapeTechnion, char* email) {
	if (!escapeTechnion || !email)
		return ET_NULL_ARG;
	if (!checkEmail(email))
		return ET_INVALID_PARAM;
	if (!escapersContains(escapeTechnion, email))
		return ET_CLIENT_EMAIL_DOES_NOT_EXIST;
	LIST_FOREACH(Order, iter, escapeTechnion->orders) {
		if (strcmp(orderGetClientEmail(iter), email) == 0) {
			listRemoveCurrent(escapeTechnion->orders);
		}
	}
	setRemove(escapeTechnion->escapers, escaperGet(escapeTechnion, email));
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionCreateOrder(EscapeTechnion escapeTechnion, char* email, TechnionFaculty faculty, int id, char* time, int num_ppl) {
	if (!escapeTechnion || !email || !time)
		return ET_NULL_ARG;
	if (!checkEmail(email) || !checkFaculty(faculty) || id < 1 || num_ppl < 1 || !checkTime(time))
		return ET_INVALID_PARAM;
	if (!escapersContains(escapeTechnion, email))
		return ET_CLIENT_EMAIL_DOES_NOT_EXIST;
	if (!checkIdInFaculty(escapeTechnion, faculty, id))
		return ET_ID_DOES_NOT_EXIST;
	int day = getDay(time), hour = getHour(time);
	if (checkOrderExists(escapeTechnion, email, day, hour))
		return ET_CLIENT_IN_ROOM;
	if (!checkRoomAvailable(escapeTechnion, faculty, id, day, hour) || !checkRoomTimes(escapeTechnion, faculty, id, hour))
		return ET_ROOM_NOT_AVAILABLE;
	Order order = orderCreate(email, faculty, id, time, num_ppl);
	if (!order)
		return ET_OUT_OF_MEMORY;
	listInsertLast(escapeTechnion->orders, order);
	orderDestroy(order);
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionRecommendRoom(EscapeTechnion escapeTechnion, char* email, int num_ppl) {
	if (!email || !escapeTechnion)
		return ET_NULL_ARG;
	if (!checkEmail(email) || num_ppl < 1)
		return ET_INVALID_PARAM;
	if (!escapersContains(escapeTechnion, email))
		return ET_CLIENT_EMAIL_DOES_NOT_EXIST;
	if (!checkRoomsFound(escapeTechnion))
		return ET_NO_ROOMS_AVAILABLE;
	Room first_in_system = roomCopy(setGetFirst(companyGetRooms(setGetFirst(escapeTechnion->companies))));
	if (!first_in_system)
		return ET_OUT_OF_MEMORY;
	TechnionFaculty save_faculty = companyGetFaculty(setGetFirst(escapeTechnion->companies));
	int min = getEqResult(escapeTechnion, first_in_system, num_ppl, email);
	int temp, save_id = roomGetId(first_in_system);
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		SET_FOREACH(Room, iter1, companyGetRooms(iter)) {
			temp = getEqResult(escapeTechnion, iter1, num_ppl, email);
			if (temp < min) {
				save_faculty = companyGetFaculty(iter);
				save_id = roomGetId(iter1);
				min = temp;
			}
			if (temp == min) {
				if (cmpFaculty(escaperFaculty(escapeTechnion, email), save_faculty, companyGetFaculty(iter)) == 1) {
					save_faculty = companyGetFaculty(iter);
					save_id = roomGetId(iter1);
					min = temp;
				}
				if (cmpFaculty(escaperFaculty(escapeTechnion, email), save_faculty, companyGetFaculty(iter)) == 0) {
					if (save_id > roomGetId(iter1)) {
						save_id = roomGetId(iter1);
						save_faculty = companyGetFaculty(iter);
						min = temp;
					}
				}
			}
		}
	}
	for (int day = 0; ; day++) {
		for (int hour = 0; ; hour++){
			int save_day = day, save_hour = hour, digit_day = 1, digit_hour = 1;
			while (save_day) {
				save_day /= 10;
				if (!save_day)
					break;
				digit_day++;
			}
			while (save_hour) {
				save_hour /= 10;
				if (!save_hour)
					break;
				digit_hour++;
			}
			char* time = malloc(digit_day + digit_hour + 1);
			myItoa(day, hour, time);
			if (escapeTechnionCreateOrder(escapeTechnion, email, save_faculty, save_id, time, num_ppl) == ET_SUCCESS) {
				free(time);
				roomDestroy(first_in_system);
				return ET_SUCCESS;
			}
			free(time);
		}
	}
	roomDestroy(first_in_system);
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionReportDay(EscapeTechnion escapeTechnion, FILE* output) {
	if (!escapeTechnion || !output)
		return ET_NULL_ARG;
	updateTotalPrice(escapeTechnion);
	int counter = 0;
	LIST_FOREACH(Order, iter, escapeTechnion->orders) {
		if (orderGetDay(iter) == 0)
			counter++;
	}
	if (counter > 0) {
		int* faculty_id = malloc(sizeof(int) * counter);
		if (!faculty_id)
			return ET_OUT_OF_MEMORY;
		int* room_id = malloc(sizeof(int) * counter);
		if (!room_id) {
			free(faculty_id);
			return ET_OUT_OF_MEMORY;
		}
		for (int i = 0; i < counter; i++) {
			faculty_id[i] = 0;
			room_id[i] = 0;
		}
		int save_hour = orderGetHour(listGetFirst(escapeTechnion->orders));
		int save_room_id = orderGetRoomId(listGetFirst(escapeTechnion->orders));
		int save_fac_id = orderGetFaculty(listGetFirst(escapeTechnion->orders));
		for (int i = 0; i < counter; i++) {
			LIST_FOREACH(Order, iter, escapeTechnion->orders) {
				if (orderGetHour(iter) < save_hour) {
					save_hour = orderGetHour(iter);
					save_room_id = orderGetRoomId(iter);
					save_fac_id = orderGetFaculty(iter);
				}
				if (orderGetHour(iter) == save_hour) {
					if (orderGetFaculty(iter) < save_fac_id) {
						save_hour = orderGetHour(iter);
						save_room_id = orderGetRoomId(iter);
						save_fac_id = orderGetFaculty(iter);
					} else if (orderGetFaculty(iter) == save_fac_id && orderGetRoomId(iter) <= save_room_id) {
						save_hour = orderGetHour(iter);
						save_room_id = orderGetRoomId(iter);
						save_fac_id = orderGetFaculty(iter);
					}
				}
			}
			faculty_id[i] = save_fac_id;
			room_id[i] = save_room_id;
			updateOrderHour(escapeTechnion, save_fac_id, save_room_id);
		}
		mtmPrintDayHeader(output, escapeTechnion->time, counter);
		printOrders(escapeTechnion, faculty_id, room_id, counter, output);
		mtmPrintDayFooter(output, escapeTechnion->time);
		free(faculty_id);
		free(room_id);
	}
	LIST_FOREACH(Order, iter, escapeTechnion->orders) {
		orderUpdateDay(iter);
	}
	escapeTechnion->time++;
	return ET_SUCCESS;
}

EscapeTechnionResult escapeTechnionReportBest(EscapeTechnion escapeTechnion, FILE* output) {
	if (!escapeTechnion || !output)
		return ET_NULL_ARG;
	int faculty_arr[FAC_NUM] = {0};
	SET_FOREACH(Company, iter, escapeTechnion->companies) {
		SET_FOREACH(Room, iter1, companyGetRooms(iter)) {
			faculty_arr[companyGetFaculty(iter)] += roomGetBudget(iter1);
		}
	}
	int sum_prices = 0;
	for (int i = 0; i < FAC_NUM; i++) {
		sum_prices += faculty_arr[i];
	}
	int top_3[3] = {0};
	mtmPrintFacultiesHeader(output, FAC_TOTAL, escapeTechnion->time, sum_prices);
	for (int i = 0; i < 3; i++) {
		top_3[i] = indexOfMax(faculty_arr, FAC_NUM);
		mtmPrintFaculty(output, i, faculty_arr[top_3[i]]);
		faculty_arr[top_3[i]] = 0;
	}
	mtmPrintFacultiesFooter(output);
	return ET_SUCCESS;
}
