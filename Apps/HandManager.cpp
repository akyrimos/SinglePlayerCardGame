#include "HandManager.h"

HandManager::HandManager() {
	vector<Card> hand;
	libptr = new Library();
}

HandManager::~HandManager()
{
	delete &hand;
	delete libptr;
}

HandManager& HandManager::operator=(const HandManager& rhs) {
	if (this == &rhs) return *this;
	delete& hand;
	delete libptr;
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




