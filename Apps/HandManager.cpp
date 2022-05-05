#include "HandManager.h"

HandManager::HandManager() {
	vector<Card> hand;
	libptr = new Library();
}

HandManager::~HandManager()
{
	delete &hand;
	// not sure if HandManager is responsible for Library
	// delete library;
}

void HandManager::Draw() {
	if (handSize >= maxHandSize) return;
	hand.push_back(libptr->Draw());
	handSize++;
}

void HandManager::DiscardHand() {
	for (int i = 0; i < handSize; i++) {
		libptr->MoveToDiscard(hand[i]);
	}

	handSize = 0;
	hand.clear();
}




