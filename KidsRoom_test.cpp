/*
 * KidsRoom_test.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: tannous
 */

#include <string>
#include <iostream>
#include "KidsRoom.h"
#include "Exceptions.h"
#include "mtmtest.h"

using namespace mtm;
using namespace escaperoom;

bool testKidsRoom() {
	KidsRoom room1((char*) "horrifying", 30, 5, 7, 12);
	room1.rate(4);
	ASSERT_EQUALS(4, room1.getRate());
	ASSERT_THROWS(EscapeRoomIllegalRateException, room1.rate(6));
	ASSERT_EQUALS("horrifying", room1.getName());
	set<string> equips;
	equips.insert("hammer");
	equips.insert("stone");
	equips.insert("gem");
	equips.insert("note");
	equips.insert("needle");
	Enigma wow("Okay", HARD_ENIGMA, 5, equips);
	Enigma wow1("Amazing", MEDIUM_ENIGMA, 5, equips);
	Enigma wow2("Sugoi", HARD_ENIGMA, 5, equips);
	Enigma wow3("Yami", EASY_ENIGMA, 5, equips);
	ASSERT_THROWS(EscapeRoomNoEnigmasException, room1.removeEnigma(wow));
	room1.addEnigma(wow1);
	ASSERT_THROWS(EscapeRoomEnigmaNotFoundException, room1.removeEnigma(wow));
	ASSERT_NO_THROW(room1.removeEnigma(wow1));
	room1.addEnigma(wow);
	room1.addEnigma(wow1);
	room1.addEnigma(wow2);
	ASSERT_THROWS(EscapeRoomEnigmaNotFoundException, room1.removeEnigma(wow3));
	room1.addEnigma(wow3);
	ASSERT_NO_THROW(room1.removeEnigma(wow3));
	ASSERT_NO_THROW(room1.removeEnigma(wow1));
	ASSERT_EQUALS(wow, room1.getHardestEnigma());
	ASSERT_NO_THROW(room1.removeEnigma(wow));
	ASSERT_NO_THROW(room1.removeEnigma(wow2));
	ASSERT_THROWS(EscapeRoomNoEnigmasException, room1.removeEnigma(wow));
	room1.addEnigma(wow);
	room1.addEnigma(wow1);
	room1.addEnigma(wow2);
	room1.addEnigma(wow3);
	KidsRoom room2(room1);
	ASSERT_EQUALS(wow, room1.getHardestEnigma());
	ASSERT_NOT_EQUAL(wow2, room1.getHardestEnigma());
	ASSERT_EQUALS(wow, room2.getHardestEnigma());
	ASSERT_NO_THROW(room2.removeEnigma(wow3));
	ASSERT_EQUALS(4, room1.getAllEnigmas().size());
	ASSERT_EQUALS(3, room2.getAllEnigmas().size());
	std::ostringstream output;
	output << room1;
	ASSERT_EQUALS(output.str(), "Kids Room: horrifying (30/5/7/12)");
	ASSERT_EQUALS(12, room1.getAgeLimit());
	std::ostringstream output1;
	ASSERT_THROWS(KidsRoomIllegalAgeLimit ,room1.setNewAgeLimit(-1));
	ASSERT_NO_THROW(room1.setNewAgeLimit(15));
	ASSERT_EQUALS(15, room1.getAgeLimit());
	output1 << room1;
	ASSERT_EQUALS(output1.str(), "Kids Room: horrifying (30/5/7/15)");
	return true;
}

int testing4() {
	RUN_TEST(testKidsRoom);
	return 0;
}
