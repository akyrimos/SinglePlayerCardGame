#ifndef CARD
#define CARD

#include <glad.h>
#include <time.h>
#include <vector>
#include "VecMat.h"
#include "Sprite.h"
#include "CardEnum.h"


using std::string;


class Card : public Sprite {

public:
	int energyCost;
	string cardName;

	struct abilities {
		CardEnum h;
		int value; 
};

private:
	int ID;

};

#endif
