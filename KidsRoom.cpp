/*
 * KidsRoom.cpp
 *
 *  Created on: Jun 25, 2017
 *      Author: tannous
 */

#include <string>
#include <iostream>
#include "KidsRoom.h"
#include "EscapeRoomWrapper.h"
#include "Exceptions.h"

using namespace mtm;
using namespace escaperoom;

KidsRoom::KidsRoom(char* name, const int& escapeTime, const int& level,
		const int& maxParticipants, const int& ageLimit) :
				EscapeRoomWrapper(name, escapeTime, level, maxParticipants), maxAge(ageLimit) {

}

void KidsRoom::setNewAgeLimit(const int& limit) {
	if (limit < 0) {
		throw KidsRoomIllegalAgeLimit();
	}
	maxAge = limit;
}

int KidsRoom::getAgeLimit() const {
	return maxAge;
}

void KidsRoom::printRoom(std::ostream& output) {
	output << *this;
}

EscapeRoomWrapper* KidsRoom::cloneRoom() {
	return new KidsRoom(*this);
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const KidsRoom& room) {
	output << "Kids Room: " << room.getName() << " (" << room.getMaxTime() << "/" << room.level() << "/"
			<< room.getMaxParticipants() << "/" << room.getAgeLimit() << ")";
	return output;
}
