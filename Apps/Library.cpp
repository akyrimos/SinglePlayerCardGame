#include "Library.h"
#include <stack>
#include <vector>
#include <random>
#include <algorithm>
#include "../Include/Card.h"

using namespace std;

Library::Library() {

	stack<Card> deckLibrary;
	vector<Card> discardPile;
	cardsRemaining = librarySize;

}

void Library::Shuffle() {

	random_shuffle(discardPile.begin(), discardPile.end());

	for (int i = 0; i < discardPile.size(); i++) {
		Add(discardPile.at(i));
	}

	discardPile.clear();

}

void Library::Add(Card foo) {

	deckLibrary.push(foo);

}

Card Library::Draw() {

	if (deckLibrary.empty()) {
		Shuffle();
	}

	Card drawnCard = deckLibrary.top();

	deckLibrary.pop();

	return drawnCard;

}