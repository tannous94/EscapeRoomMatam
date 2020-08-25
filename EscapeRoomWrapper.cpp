/*
 * EscapeRoomWrapper.cpp
 *
 *  Created on: Jun 22, 2017
 *      Author: tannous
 */

#include <string>
#include <iostream>
#include <vector>
#include "Enigma.h"
#include "Exceptions.h"
#include "EscapeRoomWrapper.h"
#include "EscapeRoom.h"

using std::vector;

using namespace mtm;
using namespace escaperoom;

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& escapeTime, const int& level,
		const int& maxParticipants) : enigmas() {
	escape_room = escapeRoomCreate(name, escapeTime, maxParticipants, level);
	if (!escape_room) {
		throw EscapeRoomMemoryProblemException();
	}
}

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& level) : enigmas() {
	escape_room = escapeRoomCreate(name, 60, 6, level);
	if (!escape_room) {
		throw EscapeRoomMemoryProblemException();
	}
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper& room) {
	escape_room = escapeRoomCopy(room.escape_room);
	if (!escape_room) {
		throw EscapeRoomMemoryProblemException();
	}
	enigmas = room.enigmas;
}

EscapeRoomWrapper::~EscapeRoomWrapper() {
	escapeRoomDestroy(escape_room);
}

EscapeRoomWrapper& EscapeRoomWrapper::operator=(const EscapeRoomWrapper& room) {
	if (this == &room) {
		return *this;
	}
	escapeRoomDestroy(escape_room); // Frees the old memory..
	escape_room = escapeRoomCopy(room.escape_room);
	if (!escape_room) {
		throw EscapeRoomMemoryProblemException();
	}
	enigmas.clear();
	enigmas = room.enigmas;
	return *this;
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper& room) const {
	return areEqualRooms(escape_room, room.escape_room);
}

bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper& room) const {
	return !(*this == room);
}

bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper& room) const {
	return isBiggerRoom(room.escape_room, escape_room);
}

bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper& room) const {
	return room < *this;
}

int EscapeRoomWrapper::level() const {
	return getLevel(escape_room);
}

void EscapeRoomWrapper::rate(const int& newRate) const {
	if (updateRate(escape_room, newRate) == ESCAPEROOM_BAD_PARAM) {
		throw EscapeRoomIllegalRateException();
	}
}

std::string EscapeRoomWrapper::getName() const {
	char* name_to_free = roomGetName(escape_room);
	std::string name = name_to_free;
	free(name_to_free);
	return name;
}

int EscapeRoomWrapper::getMaxTime() const {
	return roomGetMaxTime(escape_room);
}

int EscapeRoomWrapper::getMaxParticipants() const {
	return roomGetMaxParticipants(escape_room);
}

double EscapeRoomWrapper::getRate() const {
	return roomGetRate(escape_room);
}

void EscapeRoomWrapper::addEnigma(const Enigma& enigma) {
	enigmas.push_back(enigma);
}

void EscapeRoomWrapper::removeEnigma(const Enigma& enigma) {
	if (enigmas.empty()) {
		throw EscapeRoomNoEnigmasException();
	}
	vector<Enigma>::iterator first = enigmas.begin();
	vector<Enigma>::iterator last = enigmas.end();
	while (first != last) {
		if (*first == enigma) {
			break;
		}
		++first;
	}
	if (first == last) {
		throw EscapeRoomEnigmaNotFoundException();
	}
	enigmas.erase(first);
}

Enigma EscapeRoomWrapper::getHardestEnigma() {
	if (enigmas.empty()) {
		throw EscapeRoomNoEnigmasException();
	}
	vector<Enigma>::iterator hardest = enigmas.begin();
	for (vector<Enigma>::iterator iter = enigmas.begin(); iter != enigmas.end(); ++iter) {
		if (*iter > *hardest) {
			hardest = iter;
		}
	}
	return *hardest;
}

vector<Enigma>& EscapeRoomWrapper::getAllEnigmas() {
	return enigmas;
}

void EscapeRoomWrapper::printRoom(std::ostream& output) {
	output << *this;
}

EscapeRoomWrapper* EscapeRoomWrapper::cloneRoom() {
	return new EscapeRoomWrapper(*this);
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const EscapeRoomWrapper& room) {
	output << room.getName() << " (" << room.getMaxTime() << "/" << room.level() << "/"
			<< room.getMaxParticipants() << ")";
	return output;
}
