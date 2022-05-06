#include "Enemy.h"
#include "../Include/Actor.h"
#include "Library.h"
#include "../Include/HandManager.h"

#pragma once

class TurnManager
{
public:

	int turnNum = 1;

	TurnManager(HandManager* handptr, Enemy* enemyptr, Actor* actorptr);

	~TurnManager();

	void RunTurn();
	

private:

	Library* libptr;
	HandManager* handptr;
	Enemy* enemyptr;
	Actor* actptr;

};

