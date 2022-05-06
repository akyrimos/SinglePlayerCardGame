#include "TurnManager.h"

using namespace std;

//TurnManager tm(..)
//if using this version pass in "&hand" on instantiation
TurnManager::TurnManager(HandManager* hand, Enemy* enemy, Actor* actor) {

	handptr = hand;
	enemyptr = enemy;
	actptr = actor;

}



TurnManager::~TurnManager() {

}

void TurnManager::RunTurn() {

	handptr->DiscardHand();

	//Enemy takes turn

	actptr->RemoveArmor();
	enemyptr->RemoveArmor();

	//tick down status effects go here

	for (int i = 0; i < handptr->drawCards; i++) {
		handptr->Draw();
	}

	turnNum++;
}