#include "Library.h"
#include <stack>
#include "../Include/Card.h"

using namespace std;

Library::Library() {

	stack<Card> deckLibrary;
	vector<Card> cardVec;
	cardsRemaining = librarySize;

}

void Library::Shuffle() {
	
}

Card Library::Draw() {

	if (deckLibrary.empty()) {
		Shuffle();
	}

	Card drawnCard = deckLibrary.top();

	deckLibrary.pop();

	return drawnCard;

}