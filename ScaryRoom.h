/*
 * ScaryRoom.h
 *
 *  Created on: Jun 25, 2017
 *      Author: tannous
 */

#ifndef SCARYROOM_H_
#define SCARYROOM_H_

#include <string>
#include <iostream>
#include "EscapeRoomWrapper.h"

namespace mtm {
namespace escaperoom {

class ScaryRoom : public EscapeRoomWrapper {
	int ageLimit;
	int numOfScaryEnigmas;
public:
	// Constructs new EscapeRoom as Scary type, with age limit.
	ScaryRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas);

	// Prints the data for the scary escape room as this format:
	//      "Scary Room: <name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)"
	friend std::ostream& operator<<(std::ostream& output, const ScaryRoom& room);

	// Sets a new age limit for this scary escape room.
	void setNewAgeLimit(const int& limit);

	// Increases the number of scary enigmas in this scary escape room.
	void incNumberOfScaryEnigmas();

	// Returns the age limit of this scary escape room.
	int getAgeLimit() const;

	// Calls operator<< for scary room
	void printRoom(std::ostream& output) override;

    // Returns a pointer for a scary type room
    EscapeRoomWrapper* cloneRoom() override;

};

std::ostream& operator<<(std::ostream& output, const ScaryRoom& room);

} // end of namespace eascaperoom
} // end of namespace mtm

#endif /* SCARYROOM_H_ */
