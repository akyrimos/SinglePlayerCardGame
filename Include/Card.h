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
	Card();
	Card(string image);


	Card(string image, int ID, string Name);

	~Card();

	int EnergyCost;
	int ID;
	string Name;
	Sprite Image;

	void SetAction(CardEnum newAbility, int newValue);
	void PlayCard(Actor target);
	void initializeImage(string image);
	Actor CheckTarget(Actor target);

private:
	CardEnum ability;
	int value;

};

#endif
