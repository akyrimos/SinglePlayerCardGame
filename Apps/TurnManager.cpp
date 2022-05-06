#include "TurnManager.h"

using namespace std;

//TurnManager tm(..)
//if using this version pass in "&hand" on instantiation
TurnManager::TurnManager(Library* lib, HandManager* hand) {

	this->libptr = lib;
	this->handptr = hand;

}



TurnManager::~TurnManager() {

}

void TurnManager::RunTurn() {

	for (int i = 0; i < drawForTurn; i++) {
		handptr->Draw();
	}

}