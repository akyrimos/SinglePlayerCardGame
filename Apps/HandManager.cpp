#include "CardGame.h"
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine

HandManager::HandManager() {
	energyRemaining = maxEnergy;
	cardsRemaining = librarySize;
}

void HandManager::Draw() {
	if ((int) hand.size() >= MaxHandSize) return;
	hand.push_back(DrawFromLibrary());
}

//void HandManager::PlayCard(Actor* target, Card *selectedCard) {
//	if (!selectedCard || (energyRemaining - selectedCard->energyCost) < 0) return;
//	selectedCard->PlayCard(target);
//	selectedCard->SetPosition({ -5.0f, -5.0f });
//	energyRemaining -= selectedCard->energyCost;
//}

bool HandManager::ConsumeEnergy(Card* card)
{
	if (!card || (energyRemaining - card->energyCost) < 0) return false;
	
	energyRemaining -= card->energyCost;
	return true;
}

void HandManager::DiscardHand() {
	for (int i = 0; i < (int) hand.size(); i++)
		MoveToDiscard(hand[i]);
	hand.clear();
}

void HandManager::InitializeLibrary(Card **cards, int ncards) {
	for (int i = 0; i < ncards; i++) // drawCards; i++)
		//deckLibrary.push(cards[i]);
		discardPile.push_back(cards[i]);

	Shuffle();
}

void HandManager::Shuffle() {
	unsigned seed = clock();
	shuffle(discardPile.begin(), discardPile.end(), std::default_random_engine(seed));
	for (int i = 0; i < (int) discardPile.size(); i++)
		deckLibrary.push(discardPile[i]);
	discardPile.clear();
}

Card* HandManager::DrawFromLibrary() {
	if (deckLibrary.empty())
		Shuffle();
	Card* drawnCard = deckLibrary.top();
	deckLibrary.pop();
	return drawnCard;
}

void HandManager::MoveCardOffScreen(Card* selectedCard)
{
	selectedCard->SetPosition({ -5.0f, -5.0f });
}

void HandManager::NewFight() {
}

void HandManager::MoveToDiscard(Card* c) {
	discardPile.push_back(c);
}