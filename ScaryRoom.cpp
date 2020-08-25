/*
 * ScaryRoom.cpp
 *
 *  Created on: Jun 25, 2017
 *      Author: tannous
 */

#include <string>
#include <iostream>
#include "ScaryRoom.h"
#include "EscapeRoomWrapper.h"
#include "Exceptions.h"

using namespace mtm;
using namespace escaperoom;

ScaryRoom::ScaryRoom(char* name, const int& escapeTime, const int& level,
		const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas) :
				EscapeRoomWrapper(name, escapeTime, level, maxParticipants),
				ageLimit(ageLimit), numOfScaryEnigmas(numOfScaryEnigmas) {

}

void ScaryRoom::setNewAgeLimit(const int& limit) {
	if (limit < 0) {
		throw ScaryRoomIllegalAgeLimit();
	}
	ageLimit = limit;
}

void ScaryRoom::incNumberOfScaryEnigmas() {
	numOfScaryEnigmas++;
}

int ScaryRoom::getAgeLimit() const {
	return ageLimit;
}

void ScaryRoom::printRoom(std::ostream& output) {
	output << *this;
}

EscapeRoomWrapper* ScaryRoom::cloneRoom() {
	return new ScaryRoom(*this);
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const ScaryRoom& room) {
	output << "Scary Room: " << room.getName() << " (" << room.getMaxTime() << "/" << room.level() << "/"
			<< room.getMaxParticipants() << "/" << room.getAgeLimit() << ")";
	return output;
}
