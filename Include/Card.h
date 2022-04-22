#ifndef CARD
#define CARD

#include <glad.h>
#include <time.h>
#include <vector>
#include "VecMat.h"
#include "CardEnum.h"
#include "Sprite.h"
#include "Character.h"

using std::string;

class Card {
public:
	int Energy;
	int ID;
	string Name;
	Sprite Image;

	struct Action {
		CardEnum cardAbility;
		int value;
	};
	void PlayCard(Character target);
	Character CheckTarget(Character target);
};

#endif
