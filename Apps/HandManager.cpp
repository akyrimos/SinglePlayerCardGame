#include "HandManager.h"

HandManager::HandManager() {
	vector<Card> hand;
	libptr = nullptr;
	selected = nullptr;
}

HandManager::~HandManager()
{
	delete &hand;
}

HandManager::HandManager(Library lib) {
	vector<Card> hand;
	libptr = &lib;
	selected = nullptr;
}

HandManager& HandManager::operator=(const HandManager& rhs) {
	if (this == &rhs) return *this;
	delete& hand;
	hand = rhs.hand;
	libptr = rhs.libptr;
	maxHandSize = rhs.maxHandSize;
	drawCards = rhs.drawCards;
	return *this;
}

void HandManager::playCard(Card c)
{
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




