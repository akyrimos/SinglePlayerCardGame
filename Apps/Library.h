#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include "../Include/Card.h"

using namespace std;

class Library
{
public:

	Library();
	~Library();

	void Shuffle();
	void Add(Card foo);
	Card Draw();
	void MoveToDiscard(Card foo);


private:
	stack<Card> deckLibrary;
	vector<Card> discardPile;
	int librarySize = 10;
	int cardsRemaining;
	

};

