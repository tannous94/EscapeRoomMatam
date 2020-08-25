/*
 * Company.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: tannous
 */

#include <string>
#include <iostream>
#include <set>
#include "Company.h"
#include "ScaryRoom.h"
#include "KidsRoom.h"
#include "Exceptions.h"

using std::set;
using std::endl;

using namespace mtm;
using namespace escaperoom;

Company::Company(string name, string phoneNumber) : name(name), phoneNumber(phoneNumber) {

}

Company::~Company() {
	while(!rooms.empty()) {
		set<EscapeRoomWrapper*>::iterator iter = rooms.begin();
		delete *iter;
		rooms.erase(iter);
	}
}

Company::Company(const Company& company) : name(company.name), phoneNumber(company.phoneNumber), rooms() {
	set<EscapeRoomWrapper*>::iterator first_room = company.rooms.begin();
	set<EscapeRoomWrapper*>::iterator last_room = company.rooms.end();
	while (first_room != last_room) {
		rooms.insert((**first_room).cloneRoom());
		++first_room;
	}
}

Company& Company::operator=(const Company& company) {
	if (this == &company) {
		return *this;
	}
	name = company.name;
	phoneNumber = company.phoneNumber;
	while(!rooms.empty()) {
		set<EscapeRoomWrapper*>::iterator iter = rooms.begin();
		delete *iter;
		rooms.erase(iter);
	}
	set<EscapeRoomWrapper*>::iterator first_room = company.rooms.begin();
	set<EscapeRoomWrapper*>::iterator last_room = company.rooms.end();
	while (first_room != last_room) {
		rooms.insert((**first_room).cloneRoom());
		++first_room;
	}
	return *this;
}

void Company::createRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants) {
	try {
		EscapeRoomWrapper* room = new EscapeRoomWrapper(name, escapeTime, level, maxParticipants);
		rooms.insert(room);
	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}

void Company::createScaryRoom(char* name, const int& escapeTime, const int& level,
                                 const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas) {
	try {
		EscapeRoomWrapper* room = new ScaryRoom(name, escapeTime, level, maxParticipants, ageLimit, numOfScaryEnigmas);
		rooms.insert(room);
	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}

void Company::createKidsRoom(char* name, const int& escapeTime, const int& level,
		const int& maxParticipants, const int& ageLimit) {
	try {
		EscapeRoomWrapper* room = new KidsRoom(name, escapeTime, level, maxParticipants, ageLimit);
		rooms.insert(room);
	} catch (EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	}
}

set<EscapeRoomWrapper*> Company::getAllRooms() const {
	return rooms;
}

void Company::removeRoom(const EscapeRoomWrapper& room) {
	set<EscapeRoomWrapper*>::iterator first = rooms.begin();
	set<EscapeRoomWrapper*>::iterator last = rooms.end();
	while (first != last) {
		if (**first == room) {
			break;
		}
		++first;
	}
	if (first == last) {
		throw CompanyRoomNotFoundException();
	}
	delete *first;
	rooms.erase(first);
}

void Company::addEnigma(const EscapeRoomWrapper& room, const Enigma& enigma) {
	set<EscapeRoomWrapper*>::iterator first = rooms.begin();
	set<EscapeRoomWrapper*>::iterator last = rooms.end();
	while (first != last) {
		if (**first == room) {
			break;
		}
		++first;
	}
	if (first == last) {
		throw CompanyRoomNotFoundException();
	}
	(**first).addEnigma(enigma);
}

void Company::removeEnigma(const EscapeRoomWrapper& room, const Enigma& enigma) {
	set<EscapeRoomWrapper*>::iterator first = rooms.begin();
	set<EscapeRoomWrapper*>::iterator last = rooms.end();
	while (first != last) {
		if (**first == room) {
			break;
		}
		++first;
	}
	if (first == last) {
		throw CompanyRoomNotFoundException();
	}
	try {
		(**first).removeEnigma(enigma);
	} catch (EscapeRoomNoEnigmasException& e) {
		throw CompanyRoomHasNoEnigmasException();
	} catch (EscapeRoomEnigmaNotFoundException& e) {
		throw CompanyRoomEnigmaNotFoundException();
	}
}

void Company::addItem(const EscapeRoomWrapper& room, const Enigma& enigma, const string& element) {
	set<EscapeRoomWrapper*>::iterator first_room = rooms.begin();
	set<EscapeRoomWrapper*>::iterator last_room = rooms.end();
	while (first_room != last_room) {
		if (**first_room == room) {
			break;
		}
		++first_room;
	}
	if (first_room == last_room) {
		throw CompanyRoomNotFoundException();
	}
	vector<Enigma>::iterator first = (**first_room).getAllEnigmas().begin();
	vector<Enigma>::iterator last = (**first_room).getAllEnigmas().end();
	while (first != last) {
		if (*first == enigma) {
			break;
		}
		++first;
	}
	if (first == last) {
		throw CompanyRoomEnigmaNotFoundException();
	}
	(*first).addElement(element);
}

void Company::removeItem(const EscapeRoomWrapper& room, const Enigma& enigma, const string& element) {
	set<EscapeRoomWrapper*>::iterator first_room = rooms.begin();
	set<EscapeRoomWrapper*>::iterator last_room = rooms.end();
	while (first_room != last_room) {
		if (**first_room == room) {
			break;
		}
		++first_room;
	}
	if (first_room == last_room) {
		throw CompanyRoomNotFoundException();
	}
	vector<Enigma>::iterator first = (**first_room).getAllEnigmas().begin();
	vector<Enigma>::iterator last = (**first_room).getAllEnigmas().end();
	while (first != last) {
		if (*first == enigma) {
			break;
		}
		++first;
	}
	if (first == last) {
		throw CompanyRoomEnigmaNotFoundException();
	}
	try {
		(*first).removeElement(element);
	} catch (EnigmaNoElementsException& e) {
		throw CompanyRoomEnigmaHasNoElementsException();
	} catch (EnigmaElementNotFoundException& e) {
		throw CompanyRoomEnigmaElementNotFoundException();
	}
}

set<EscapeRoomWrapper*> Company::getAllRoomsByType(RoomType type) const {
	set<EscapeRoomWrapper*> filtered_set;
	set<EscapeRoomWrapper*>::iterator first_room = rooms.begin();
	set<EscapeRoomWrapper*>::iterator last_room = rooms.end();
	while (first_room != last_room) {
		if (type == BASE_ROOM) {
			if (dynamic_cast<ScaryRoom*>(*first_room) == nullptr
					&& dynamic_cast<KidsRoom*>(*first_room) == nullptr) {
				filtered_set.insert(*first_room);
			}
		}
		if (type == SCARY_ROOM) {
			if (dynamic_cast<ScaryRoom*>(*first_room) != nullptr) {
				filtered_set.insert(*first_room);
			}
		}
		if (type == KIDS_ROOM) {
			if (dynamic_cast<KidsRoom*>(*first_room) != nullptr) {
				filtered_set.insert(*first_room);
			}
		}
		++first_room;
	}
	return filtered_set;
}

EscapeRoomWrapper* Company::getRoomByName(const string& name) const {
	set<EscapeRoomWrapper*>::iterator first_room = rooms.begin();
	set<EscapeRoomWrapper*>::iterator last_room = rooms.end();
	while (first_room != last_room) {
		if ((**first_room).getName() == name) {
			break;
		}
		++first_room;
	}
	if (first_room == last_room) {
		throw CompanyRoomNotFoundException();
	}
	return *first_room;
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const Company& company) {
	output << company.name << " : " << company.phoneNumber << endl;
	if (company.getAllRooms().empty())
		return output;
	set<EscapeRoomWrapper*>::iterator iter;
	for (int i = 0; i < 3; i++) {
		set<EscapeRoomWrapper*> roomsByType = company.getAllRoomsByType((RoomType)i);
		for (iter = roomsByType.begin(); iter != roomsByType.end(); ++iter) {
			(**iter).printRoom(output);
			output << endl;
		}
	}
	return output;
}
