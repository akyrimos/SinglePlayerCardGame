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
	Card(int EnergyCost, int ID, string name);

	~Card();

	int EnergyCost;
	int ID;
	string filepath;
	Sprite Image;

	void SetAction(CardEnum newAbility, int newValue);
	void PlayCard(Actor target);
	void initializeImage(float Zvalue);
	void Display();
	Actor CheckTarget(Actor target);

private:
	CardEnum ability;
	int value;

};

#endif
