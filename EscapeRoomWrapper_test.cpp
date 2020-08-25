/*
 * EscapeRoomWrapper_test.cpp
 *
 *  Created on: Jun 24, 2017
 *      Author: tannous
 */

#include "EscapeRoomWrapper.h"
#include "Enigma.h"
#include "mtmtest.h"
#include "Exceptions.h"

using namespace mtm;
using namespace escaperoom;

bool testEscapeRoomWrapperCtors() {
	EscapeRoomWrapper room1((char*) "Muhaha", 50, 2, 7);
	EscapeRoomWrapper room2((char*) "Okay", 30, 5, 15);
	EscapeRoomWrapper room3((char*) "Wow", 3);
	EscapeRoomWrapper room4(room1);
	EscapeRoomWrapper room5(room3);
	ASSERT_NOT_EQUAL("Muhahaha", room1.getName());
	ASSERT_NOT_EQUAL("Muhaha", room5.getName());
	ASSERT_EQUALS("Muhaha", room1.getName());
	ASSERT_EQUALS("Okay", room2.getName());
	ASSERT_EQUALS("Wow", room3.getName());
	ASSERT_EQUALS("Muhaha", room4.getName());
	ASSERT_EQUALS("Wow", room5.getName());
	ASSERT_EQUALS(50, room1.getMaxTime());
	ASSERT_EQUALS(30, room2.getMaxTime());
	ASSERT_EQUALS(60, room3.getMaxTime());
	ASSERT_EQUALS(50, room4.getMaxTime());
	ASSERT_EQUALS(60, room5.getMaxTime());
	ASSERT_EQUALS(7, room1.getMaxParticipants());
	ASSERT_EQUALS(15, room2.getMaxParticipants());
	ASSERT_EQUALS(6, room3.getMaxParticipants());
	ASSERT_EQUALS(7, room4.getMaxParticipants());
	ASSERT_EQUALS(6, room5.getMaxParticipants());
	ASSERT_EQUALS(0, room1.getRate());
	ASSERT_EQUALS(0, room2.getRate());
	ASSERT_EQUALS(0, room3.getRate());
	ASSERT_EQUALS(0, room4.getRate());
	ASSERT_EQUALS(0, room5.getRate());
	ASSERT_EQUALS(2, room1.level());
	ASSERT_EQUALS(5, room2.level());
	ASSERT_EQUALS(3, room3.level());
	ASSERT_EQUALS(2, room4.level());
	ASSERT_EQUALS(3, room5.level());
	room5 = room1;
	ASSERT_EQUALS("Muhaha", room1.getName());
	ASSERT_EQUALS(50, room1.getMaxTime());
	ASSERT_EQUALS(7, room1.getMaxParticipants());
	ASSERT_EQUALS(0, room1.getRate());
	ASSERT_EQUALS(2, room1.level());
	ASSERT_EQUALS("Muhaha", room5.getName());
	ASSERT_EQUALS(50, room5.getMaxTime());
	ASSERT_EQUALS(7, room5.getMaxParticipants());
	ASSERT_EQUALS(0, room5.getRate());
	ASSERT_EQUALS(2, room5.level());
	ASSERT_NOT_EQUAL("Wow", room5.getName());
	ASSERT_THROWS(EscapeRoomIllegalRateException, room1.rate(6));
	ASSERT_THROWS(EscapeRoomIllegalRateException, room1.rate(-1));
	room1.rate(4);
	ASSERT_EQUALS(4, room1.getRate());
	ASSERT_EQUALS(0, room5.getRate());
	ASSERT_NOT_EQUAL(4, room5.getRate());
	room1.rate(5);
	ASSERT_NOT_EQUAL(4, room1.getRate());
	ASSERT_EQUALS(4.5, room1.getRate());
	room1.rate(1);
	ASSERT_EQUALS((double)10/3, room1.getRate());
	ASSERT_EQUALS(0, room2.getRate());
	ASSERT_EQUALS(0, room3.getRate());
	ASSERT_EQUALS(0, room4.getRate());
	return true;
}

bool testEscapeRoomWrapperOperators() {
	EscapeRoomWrapper room1((char*) "Muhaha", 50, 2, 7);
	EscapeRoomWrapper room6((char*) "Muhaha", 50, 2, 8);
	EscapeRoomWrapper room7((char*) "Muhahaha", 50, 2, 7);
	EscapeRoomWrapper room2((char*) "Okay", 30, 5, 15);
	EscapeRoomWrapper room3((char*) "Wow", 3);
	EscapeRoomWrapper room4(room1);
	EscapeRoomWrapper room5(room3);
	room1.rate(4);
	std::ostringstream output;
	output << room1 << room2 << room3 << room4 << room5;
	ASSERT_EQUALS(output.str(), "Muhaha (50/2/7)"
			"Okay (30/5/15)"
			"Wow (60/3/6)"
			"Muhaha (50/2/7)"
			"Wow (60/3/6)");
	ASSERT_TRUE(room1 != room2);
	ASSERT_TRUE(room1 != room6);
	ASSERT_TRUE(room1 != room7);
	ASSERT_FALSE(room1 == room2);
	EscapeRoomWrapper room8((char*) "Eqq", 30, 6, 2);
	EscapeRoomWrapper room9((char*) "Eqq", 30, 3, 1);
	ASSERT_TRUE(room8 == room9);
	ASSERT_TRUE(room2 == room2);
	ASSERT_TRUE(room3 < room9);
	ASSERT_FALSE(room8 < room9);
	ASSERT_FALSE(room8 > room9);
	ASSERT_FALSE(room9 < room8);
	ASSERT_FALSE(room9 > room8);
	ASSERT_TRUE(room8 > room3);
	ASSERT_TRUE(room9 > room3);
	return true;
}

bool testEscapeRoomWrapperEnigmas() {
	EscapeRoomWrapper room1((char*) "Muhaha", 50, 2, 7);
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
	EscapeRoomWrapper room2(room1);
	ASSERT_EQUALS(wow, room1.getHardestEnigma());
	ASSERT_NOT_EQUAL(wow2, room1.getHardestEnigma());
	ASSERT_EQUALS(wow, room2.getHardestEnigma());
	ASSERT_NO_THROW(room2.removeEnigma(wow3));
	ASSERT_EQUALS(4, room1.getAllEnigmas().size());
	ASSERT_EQUALS(3, room2.getAllEnigmas().size());
	room1 = room2;
	ASSERT_THROWS(EscapeRoomEnigmaNotFoundException, room1.removeEnigma(wow3));
	ASSERT_EQUALS(3, room1.getAllEnigmas().size());
	ASSERT_NO_THROW(room1.removeEnigma(wow));
	ASSERT_NO_THROW(room1.removeEnigma(wow1));
	ASSERT_NO_THROW(room1.removeEnigma(wow2));
	ASSERT_EQUALS(0, room1.getAllEnigmas().size());
	ASSERT_EQUALS(3, room2.getAllEnigmas().size());
	return true;
}

int testing3() {
	RUN_TEST(testEscapeRoomWrapperCtors);
	RUN_TEST(testEscapeRoomWrapperOperators);
	RUN_TEST(testEscapeRoomWrapperEnigmas);
	return 0;
}
