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
	Card(int energyCost, int id, string name);

	~Card();

	int energyCost;
	int id;
	string filepath;
	Sprite image;

	void SetAction(CardEnum newAbility, int newValue);
	void PlayCard(Actor* target);
	void InitializeImage(float Zvalue);
	void Display();
	Actor CheckTarget(Actor target);

private:
	CardEnum ability;
	int value;

};

#endif
