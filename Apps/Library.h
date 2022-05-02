#pragma once
#include <iostream>
#include <stack>
#include "../Include/Card.h"

using namespace std;

class Library
{
public:

	Library();
	~Library();

	void Shuffle();
	void Draw(int drawNum);


private:
	stack<Card> deckLibrary;


};

