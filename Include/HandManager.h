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
	void playCard(Card c);
	void Draw();
	void Discard();

private:
	int maxHandSize = 10;
	int drawCards = 5;
	int handSize = 0;
	vector<Card> hand;
	Library* libptr;


};
#endif
