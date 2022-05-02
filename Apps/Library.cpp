#include "Library.h"
#include <stack>
#include "../Include/Card.h"

using namespace std;

Library::Library() {

	stack<Card> deckLibrary;
	vector<Card> cardVec;
	cardsRemaining = librarySize;

}