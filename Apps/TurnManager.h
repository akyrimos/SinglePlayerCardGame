#include "Enemy.h"
#include "../Include/Actor.h"
#include "Library.h"
#include "../Include/HandManager.h"

#pragma once

class TurnManager
{
public:

	int turnNum = 1;
	int drawForTurn = 5;

	TurnManager(Library* libptr, HandManager* handptr);

	~TurnManager();

	void RunTurn();
	

private:

	Library* libptr;
	HandManager* handptr;

};

