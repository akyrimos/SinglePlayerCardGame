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


private:
	stack<Card> deckLibrary;
	vector<Card> cardVec;
	int librarySize = 10;
	int cardsRemaining;
	

};

