#ifndef CARD
#define CARD

#include <glad.h>
#include <time.h>
#include <vector>
#include "VecMat.h"
#include "CardEnum.h"
#include "Sprite.h"
#include "Actor.h"

using std::string;

class Card {
public:
	/*
	* Constructor
	*/
	Card(string image);


	Card(string image, int ID, string Name);

	~Card();

	int Energy;
	int ID;
	string Name;
	Sprite Image;

	void SetAction(CardEnum newAbility, int newValue);
	void PlayCard(Actor target);
	Actor CheckTarget(Actor target);

private:
	struct Action {
		CardEnum ability;
		int value;
	};

	Action *CardAction;
};

#endif
