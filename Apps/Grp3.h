#ifndef GRP3
#define GRP3
#include "Sprite.h"
#include <stack>
#include<string> 

using namespace std;
const int MaxHandSize = 10;

class Actor : public Sprite {
public:
	int health = 10;
	int maxHealth = 10;
	int tempArmor = 0;
	int *status = NULL;
	string message;
	bool CheckifAlive() { return health > 0; }
	bool IsPlayer() { return false; }
	void ChangeHealth(int healthToAdd) { if ((health += healthToAdd) > maxHealth) health = maxHealth; }
	void TakeDamage(int damage) {
		tempArmor -= damage;
		if (tempArmor < 0) {
			health -= abs(tempArmor);
			RemoveArmor();
			CheckifAlive();
			message = "ouch! my health now "+to_string(health);
		//	cout << "ouch! my health now " << health << endl;
		}
	}
	void RemoveArmor() { tempArmor = 0; }
};

enum class CardEnum { Undefined = 0, Attack, Defend, Debuff, Buff, Power, NActions };

class Card : public Sprite {
public:
	vec3 position;
	int energyCost;
	int id;
	CardEnum ability;
	int value;
	Card() {
		energyCost = 1;
		id = 1;
		value = 6;
		ability = CardEnum::Attack;
	}
	Card(int EnergyCost, int ID, string name) {
		energyCost = EnergyCost;
		id = ID;
		ability = CardEnum::Undefined;
	}
	void SetAction(CardEnum newAbility, int newValue) {
		ability = newAbility;
		value = newValue;
	}
	void PlayCard(Actor* target) {
		const char *cardNames[] = { "Undefined", "Attack", "Defend", "Debuff", "Buff", "Power" };
		cout << cardNames[(int) ability] << endl;
		if (!target->IsPlayer() && ability == CardEnum::Attack)
			target->TakeDamage(value);
	}
};

class Enemy : public Actor {
public:
	Enemy();
	Enemy(int startinghealth);
	void Action();
	void AddAction(CardEnum actionAdd, int valueAdd);
	void GainArmor();
	struct EnemyAction {
		CardEnum actionType;
		int actionValue;
	};
	vector<EnemyAction> actions;
};

class HandManager {
public:
	HandManager();
	void PlayCard(Actor* target, Card *card);
	void Draw();
	void DiscardHand();
	void Shuffle();
	Card *DrawFromLibrary();
	void MoveToDiscard(Card* c);
	void InitializeLibrary(Card **cards, int ncards);
	stack<Card *> deckLibrary;
	vector<Card *> discardPile;
	int librarySize = 10;
	int cardsRemaining;
	int drawCards = 5;
	int maxEnergy = 3;
	int energyRemaining = maxEnergy;
	vector<Card *> hand;
};

#endif
