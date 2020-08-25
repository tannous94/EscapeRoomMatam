/*
 * Enigma.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: tannous
 */

#include <string>
#include <iostream>
#include "Exceptions.h"
#include "Enigma.h"

using namespace mtm;
using namespace escaperoom;

Enigma::Enigma(const std::string& name, const Difficulty& difficulty, const int& numOfElements, const set<string>& elements) :
		name(name), difficulty(difficulty), numOfElements(numOfElements), elements(elements) {
	int size = elements.size();
	if (size != numOfElements) {
		throw EnigmaIllegalSizeParamException();
	}
}

Enigma::Enigma(const std::string& name, const Difficulty& difficulty) : name(name), difficulty(difficulty), numOfElements(0), elements() {

}

bool Enigma::operator==(const Enigma& enigma) const {
	if (difficulty == enigma.difficulty) {
		if (name == enigma.name) {
			return true;
		}
	}
	return false;
}

bool Enigma::operator!=(const Enigma& enigma) const {
	return !(*this == enigma);
}

bool Enigma::operator<(const Enigma& enigma) const {
	return difficulty < enigma.difficulty;
}

bool Enigma::operator>(const Enigma& enigma) const {
	return difficulty > enigma.difficulty;
}

bool Enigma::areEqualyComplex(const Enigma& enigma) const {
	return (difficulty == enigma.difficulty) && (numOfElements == enigma.numOfElements);
}

Difficulty Enigma::getDifficulty() const {
	return difficulty;
}

string Enigma::getName() const {
	return name;
}

void Enigma::addElement(const string& element) {
	elements.insert(element);
	numOfElements++;
}

void Enigma::removeElement(const string& element) {
	if (numOfElements == 0) {
		throw EnigmaNoElementsException();
	}
	if (!elements.count(element)) {
		throw EnigmaElementNotFoundException();
	}
	elements.erase(element);
	numOfElements--;
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const Enigma& enigma) {
	output << enigma.getName() << " (" << enigma.getDifficulty() << ") " << enigma.numOfElements;
	return output;
}
