/*
 * Enigma_test.cpp
 *
 *  Created on: Jun 24, 2017
 *      Author: tannous
 */

#include "Enigma.h"
#include "mtmtest.h"
#include "Exceptions.h"

using namespace mtm;
using namespace escaperoom;

bool testEnigma() {
	set<string> equips;
	equips.insert("hammer");
	equips.insert("stone");
	equips.insert("gem");
	equips.insert("note");
	equips.insert("needle");
	set<string> equips1;
	equips1.insert("asd1");
	equips1.insert("asd2");
	equips1.insert("asd3");
	equips1.insert("asd4");
	equips1.insert("asd5");
	equips1.insert("asd6");
	equips1.insert("asd7");
	equips1.insert("asd8");
	equips1.insert("asd9");
	set<string> equips2;
	equips2.insert("asd1");
	equips2.insert("asd2");
	equips2.insert("asd3");
	equips2.insert("asd4");
	equips2.insert("asd5");
	equips2.insert("asd6");
	equips2.insert("asd7");
	equips2.insert("asd8");
	equips2.insert("asd9");
	equips2.insert("asd10");
	equips2.insert("asd11");
	ASSERT_TRUE(equips.size() == 5);
	ASSERT_THROWS(EnigmaIllegalSizeParamException, Enigma("Eren", MEDIUM_ENIGMA, 4, equips));
	Enigma eren("Eren", MEDIUM_ENIGMA, 5, equips);
	Enigma eren1("Eren1", MEDIUM_ENIGMA, 5, equips);
	ASSERT_EQUALS(MEDIUM_ENIGMA, eren.getDifficulty());
	ASSERT_EQUALS("Eren", eren.getName());
	Enigma mikasa("Mikasa", HARD_ENIGMA, 9, equips1);
	Enigma mikasa1("Mikasa", HARD_ENIGMA, 11, equips2);
	Enigma mikasa2("Fake", HARD_ENIGMA, 9, equips1);
	ASSERT_EQUALS(HARD_ENIGMA, mikasa.getDifficulty());
	ASSERT_TRUE(mikasa != eren);
	ASSERT_TRUE(eren1 != eren);
	ASSERT_FALSE(mikasa == eren);
	ASSERT_TRUE(mikasa > eren);
	ASSERT_TRUE(eren < mikasa);
	ASSERT_TRUE(mikasa1 == mikasa);
	ASSERT_FALSE(mikasa1 != mikasa);
	ASSERT_TRUE(mikasa.areEqualyComplex(mikasa2));
	ASSERT_FALSE(mikasa.areEqualyComplex(mikasa1));
	std::ostringstream output;
	output << eren << mikasa;
	ASSERT_EQUALS(output.str(), "Eren (1) 5Mikasa (2) 9");
	Enigma jean("Jean", EASY_ENIGMA);
	ASSERT_EQUALS(EASY_ENIGMA, jean.getDifficulty());
	std::ostringstream output1;
	output1 << jean;
	ASSERT_EQUALS(output1.str(), "Jean (0) 0");
	ASSERT_TRUE(eren > jean);
	ASSERT_THROWS(EnigmaNoElementsException, jean.removeElement("hammer"));
	jean.addElement("hammer");
	std::ostringstream output2;
	output2 << jean;
	ASSERT_EQUALS(output2.str(), "Jean (0) 1");
	ASSERT_THROWS(EnigmaElementNotFoundException, jean.removeElement("stone"));
	Enigma lora(jean);
	ASSERT_NO_THROW(lora.removeElement("hammer"));
	ASSERT_NO_THROW(eren.removeElement("stone"));
	mikasa2.removeElement("asd4");
	ASSERT_FALSE(mikasa.areEqualyComplex(mikasa2));
	mikasa2.addElement("asd99");
	ASSERT_TRUE(mikasa.areEqualyComplex(mikasa2));
	mikasa2.removeElement("asd99");
	ASSERT_THROWS(EnigmaElementNotFoundException, mikasa2.removeElement("asd4"));
	mikasa2.removeElement("asd5");
	std::ostringstream output3;
	output3 << eren << mikasa2;
	ASSERT_EQUALS(output3.str(), "Eren (1) 4Fake (2) 7");
	lora = eren;
	std::ostringstream output5;
	output5 << lora;
	ASSERT_EQUALS(output5.str(), "Eren (1) 4");
	eren.addElement("asd99");
	eren.addElement("asd98");
	jean.removeElement("hammer");
	std::ostringstream output4;
	output4 << eren << jean;
	ASSERT_EQUALS(output4.str(), "Eren (1) 6Jean (0) 0");
	return true;
}

int testing2() {
	RUN_TEST(testEnigma);
	return 0;
}
