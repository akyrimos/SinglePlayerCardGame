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
	HandManager(Library* lib);
	//HandManager& operator=(const HandManager& rhs);
	void playCard(Actor* target);
	void playCard();
	void Draw();
	void DiscardHand();
	void SetCardPosition(float x, float y, int index);
	void SelectCard(Card* c);
	void DeselectCard();
	int maxHandSize = 10;
	int drawCards = 5;
	int handSize = 0;
	vector<Card*> hand;

private:
	Card* selected;
	Library* libptr;
};
#endif
