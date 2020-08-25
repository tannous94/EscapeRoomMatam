/*
 * Company_test.cpp
 *
 *  Created on: Jun 27, 2017
 *      Author: tannous
 */

#include <string>
#include <iostream>
#include "Company.h"
#include "Exceptions.h"
#include "mtmtest.h"

using std::endl;
using namespace mtm;
using namespace escaperoom;

bool testCompany() {
	Company comp("Comp", "0541234567");
	comp.createRoom((char*) "okay", 50, 4, 5);
	comp.createScaryRoom((char*) "scary", 60, 8, 6, 15, 5);
	comp.createKidsRoom((char*) "kids", 30, 2, 5, 18);
	ASSERT_EQUALS(3, comp.getAllRooms().size());
	ASSERT_NO_THROW(comp.removeRoom(EscapeRoomWrapper((char*) "okay", 50, 4, 5)));
	ASSERT_THROWS(CompanyRoomNotFoundException ,comp.removeRoom(EscapeRoomWrapper((char*) "okay", 50, 4, 5)));
	ASSERT_EQUALS(2, comp.getAllRooms().size());
	comp.createRoom((char*) "okay", 50, 4, 5);
	comp.createRoom((char*) "okay1", 45, 3, 3);
	ASSERT_EQUALS(4, comp.getAllRooms().size());
	KidsRoom room4((char*) "kids", 30, 2, 5, 18);
    ScaryRoom room1((char*) "scary", 60, 8, 6, 15, 5);
    EscapeRoomWrapper room5((char*) "okay", 50, 4, 5);
    EscapeRoomWrapper room2((char*) "okay1", 45, 3, 3);
    EscapeRoomWrapper room3((char*) "okay2", 40, 2, 4);
    Enigma enigma1("e1",EASY_ENIGMA);
    Enigma enigma2("e2",HARD_ENIGMA);
    Enigma enigma3("e3",MEDIUM_ENIGMA);
    ASSERT_THROWS(CompanyRoomNotFoundException, comp.addEnigma(room3, enigma1));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException, comp.removeEnigma(room2, enigma2));
    ASSERT_NO_THROW(comp.addEnigma(room2, enigma1));
    ASSERT_NO_THROW(comp.addEnigma(room1, enigma2));
    ASSERT_NO_THROW(comp.addEnigma(room1, enigma1));
    ASSERT_THROWS(CompanyRoomNotFoundException, comp.removeEnigma(room3, enigma1));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp.removeEnigma(room2, enigma2));
    ASSERT_NO_THROW(comp.removeEnigma(room2, enigma1));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException, comp.removeEnigma(room2, enigma1));
    ASSERT_THROWS(CompanyRoomNotFoundException, comp.addItem(room3, enigma1, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp.addItem(room1, enigma3, "asd"));
    ASSERT_NO_THROW(comp.addItem(room1, enigma1, "asd"));
    ASSERT_THROWS(CompanyRoomNotFoundException, comp.removeItem(room3, enigma1, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp.removeItem(room1, enigma3, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException, comp.removeItem(room1, enigma2, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException, comp.removeItem(room1, enigma1, "asd1"));
    ASSERT_NO_THROW(comp.removeItem(room1, enigma1, "asd"));
    ASSERT_EQUALS(room1, *comp.getRoomByName("scary"));
    ASSERT_EQUALS(room2, *comp.getRoomByName("okay1"));
    ASSERT_THROWS(CompanyRoomNotFoundException, comp.getRoomByName("okay2"));
    ASSERT_EQUALS(4, comp.getAllRooms().size());
    ASSERT_EQUALS(1, comp.getAllRoomsByType(SCARY_ROOM).size());
    comp.createScaryRoom((char*) "scary1", 60, 8, 6, 17, 5);
    comp.createScaryRoom((char*) "scary2", 55, 6, 5, 12, 6);
    comp.createScaryRoom((char*) "scary3", 50, 7, 5, 13, 3);
    ASSERT_EQUALS(4, comp.getAllRoomsByType(SCARY_ROOM).size());
    ASSERT_EQUALS(1, comp.getAllRoomsByType(KIDS_ROOM).size());
    ASSERT_EQUALS(2, comp.getAllRoomsByType(BASE_ROOM).size());
    comp.createKidsRoom((char*) "kids1", 33, 4, 6, 17);
    comp.createKidsRoom((char*) "kids2", 40, 5, 9, 20);
    ASSERT_EQUALS(3, comp.getAllRoomsByType(KIDS_ROOM).size());
    Company comp1(comp);
    ASSERT_EQUALS(3, comp1.getAllRoomsByType(KIDS_ROOM).size());
    ASSERT_EQUALS(room1, *comp1.getRoomByName("scary"));
    ASSERT_EQUALS(2, comp1.getRoomByName("scary")->getAllEnigmas().size());
    ASSERT_EQUALS(2, comp.getRoomByName("scary")->getAllEnigmas().size());
    ASSERT_EQUALS(9, comp1.getAllRooms().size());
    ASSERT_NO_THROW(comp1.removeRoom(room4));
    Enigma enigma5("e5",EASY_ENIGMA);
    ASSERT_THROWS(CompanyRoomNotFoundException ,comp1.removeRoom(room4));
    ASSERT_THROWS(CompanyRoomNotFoundException, comp1.removeItem(room3, enigma1, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp1.removeItem(room1, enigma3, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException, comp1.removeItem(room1, enigma2, "asd"));
    ASSERT_THROWS(CompanyRoomNotFoundException, comp1.removeItem(room3, enigma1, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp1.removeItem(room1, enigma3, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException, comp1.removeItem(room1, enigma2, "asd"));
    ASSERT_NO_THROW(comp1.removeEnigma(room1, enigma1));
    ASSERT_EQUALS(1, comp1.getRoomByName("scary")->getAllEnigmas().size());
    ASSERT_EQUALS(2, comp.getRoomByName("scary")->getAllEnigmas().size());
    ASSERT_NO_THROW(comp1.addEnigma(room1, enigma5));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp.removeEnigma(room1, enigma5));
    ASSERT_EQUALS(8, comp1.getAllRooms().size());
    ASSERT_EQUALS(9, comp.getAllRooms().size());
    comp = comp1;
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp1.removeEnigma(room1, enigma1));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp.removeEnigma(room1, enigma1));
    ASSERT_EQUALS(2, comp1.getRoomByName("scary")->getAllEnigmas().size());
    ASSERT_EQUALS(2, comp.getRoomByName("scary")->getAllEnigmas().size());
    ASSERT_THROWS(CompanyRoomNotFoundException ,comp.removeRoom(room4));
    ASSERT_THROWS(CompanyRoomNotFoundException, comp.removeItem(room3, enigma1, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp.removeItem(room1, enigma3, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException, comp.removeItem(room1, enigma2, "asd"));
    ASSERT_THROWS(CompanyRoomNotFoundException, comp.removeItem(room3, enigma1, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, comp.removeItem(room1, enigma3, "asd"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException, comp.removeItem(room1, enigma2, "asd"));
    ASSERT_EQUALS(8, comp.getAllRooms().size());
    ASSERT_EQUALS(8, comp1.getAllRooms().size());
    ASSERT_NO_THROW(comp.removeEnigma(room1, enigma5));
    ASSERT_NO_THROW(comp1.removeRoom(room5));
    ASSERT_EQUALS(8, comp.getAllRooms().size());
    ASSERT_EQUALS(7, comp1.getAllRooms().size());
    ASSERT_THROWS(CompanyRoomNotFoundException ,comp1.removeRoom(room5));
	return true;
}

bool testCompany1() {
    Company company("c1","1234");
    ASSERT_NO_THROW(company.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(company.createRoom((char *) "r2", 60, 3, 4));
    ASSERT_NO_THROW(company.createRoom((char *) "r3", 60, 5, 6));
    ASSERT_NO_THROW(company.createKidsRoom((char *) "r4", 60, 2, 2,7));
    ASSERT_NO_THROW(company.createScaryRoom((char *) "r5", 60, 2, 2,11,20));
    ASSERT_NO_THROW(company.removeRoom(EscapeRoomWrapper((char*)"r1",60,2,2)));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeRoom(EscapeRoomWrapper((char*)"r1",60,2,2)));
    ASSERT_NO_THROW(company.removeRoom(ScaryRoom((char*)"r5",60,2,2,11,20)));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeRoom(ScaryRoom((char*)"r5",60,2,2,11,20)));
	return true;
}

bool testCompany2() {
    Company company("c1","1234");
    company.createRoom((char *) "r1", 60, 2, 2);
    company.createRoom((char *) "r2", 60, 3, 4);
    EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room2((char *) "r2", 60, 2, 2);
    Enigma enigma1("e1",EASY_ENIGMA);
    Enigma enigma2("e2",HARD_ENIGMA);

    ASSERT_THROWS(CompanyRoomNotFoundException , company.addEnigma(room2, enigma2));
    ASSERT_NO_THROW(company.addEnigma(room1, enigma1));
    ASSERT_NO_THROW(company.addEnigma(room1, enigma2));
    ASSERT_NO_THROW(company.removeEnigma(room1,enigma1));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException , company.removeEnigma(room1,enigma1));
    ASSERT_NO_THROW(company.removeEnigma(room1,enigma2));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException , company.removeEnigma(room1,enigma2));
	return true;
}

bool testCompany3() {
    Company company("c1","1234");
    company.createRoom((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
    EscapeRoomWrapper room2((char *) "r2", 60, 2, 2);
    Enigma enigma1("e1",EASY_ENIGMA);
    Enigma enigma2("e2",HARD_ENIGMA);

    company.addEnigma(room1,enigma1);
    ASSERT_NO_THROW(company.addItem(room1,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException ,company.addItem(room1,enigma2,"x"));
    ASSERT_THROWS(CompanyRoomNotFoundException ,company.addItem(room2,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomNotFoundException, company.removeItem(room2,enigma1,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException , company.removeItem(room1,enigma2,"x"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException , company.removeItem(room1,enigma1,"y"));
    ASSERT_NO_THROW(company.removeItem(room1,enigma1,"x"));

    company.addEnigma(room1,enigma2);
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException , company.removeItem(room1,enigma2,"x"));
	return true;
}

int testing1() {
	RUN_TEST(testCompany);
	RUN_TEST(testCompany1);
	RUN_TEST(testCompany2);
	RUN_TEST(testCompany3);
	return 0;
}
