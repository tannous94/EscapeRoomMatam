/*
 * KidsRoom.h
 *
 *  Created on: Jun 25, 2017
 *      Author: tannous
 */

#ifndef KIDSROOM_H_
#define KIDSROOM_H_

#include <string>
#include <iostream>
#include "EscapeRoomWrapper.h"

namespace mtm {
namespace escaperoom {

class KidsRoom : public EscapeRoomWrapper {
	int maxAge;
public:
	// Constructs a new EscapeRoom as Kids type, with a max age.
	KidsRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit);

	// Prints the data for the kids escape room as this format:
	//      "Kids Room: <name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)"
	friend std::ostream& operator<<(std::ostream& output, const KidsRoom& room);

	// Sets new age limit for this kids escape room (new max age).
	void setNewAgeLimit(const int& limit);

	// Returns age limit for this kids escape room.
	int getAgeLimit() const;

	// Calls operator<< for kids room
	void printRoom(std::ostream& output) override;

    // Returns a pointer for a kids type room
    EscapeRoomWrapper* cloneRoom() override;

};

std::ostream& operator<<(std::ostream& output, const KidsRoom& room);

} // end of namespace eascaperoom
} // end of namespace mtm

#endif /* KIDSROOM_H_ */
