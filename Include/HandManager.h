#ifndef HANDMANAGER
#define HANDMANAGER
#pragma once
#include "Card.h"
#include "Library.h"
#include "vector"

class HandManager
{
public:
	HandManager();
	~HandManager();
	HandManager(Library lib);
	HandManager& operator=(const HandManager& rhs);
	void playCard(Card c);
	void Draw();
	void DiscardHand();

private:
	int maxHandSize = 10;
	int drawCards = 5;
	int handSize = 0;
	vector<Card> hand;
	Card* selected;
	Library* libptr;
};
#endif
