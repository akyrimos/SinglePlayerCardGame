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
	void GainArmor(int value) { health + value; }
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

enum class EffectType { Undefined = 0, Attack, Defend, Debuff, Buff, Power, NActions };
enum class TargetType { Undefined = 0, Player, Enemy, None, NActions };
class Action {
	int value;
	EffectType effect;
	Action(int val, EffectType eff) :value(val), effect(eff) {};
};
class Card : public Sprite {
public:
	vec3 position;
	int energyCost;
	int id;
	EffectType ability;
	stack<Action> actions;
	TargetType tType;
	int value;
	Card() {
		energyCost = 1;
		value = 6;
		ability = EffectType::Attack;
		tType = TargetType::Enemy;
	}

	Card(int energycost, int value, EffectType ability, TargetType thing) {
		this->energyCost = energycost;
		this->value = value;
		this->ability = ability;
		this->tType = thing;
	}
	// TODO: change to initialize value

	void SetAction(EffectType newAbility, int newValue) {
		ability = newAbility;
		value = newValue;
	}
	void PlayCard(Actor* target) {
		const char *cardNames[] = { "Undefined", "Attack", "Defend", "Debuff", "Buff", "Power" };
		cout << "My health now: " << target->health;
		cout << cardNames[(int) ability] << endl;
		if (ValidTarget(target)) {
			if (!target->IsPlayer() && ability == EffectType::Attack)
				target->TakeDamage(value);
			if (target->IsPlayer() && ability == EffectType::Defend)
				target->GainArmor(value);
				cout << "My health now: " << target->health;
		}
	}
	bool ValidTarget(Actor* target) {
		if (!target) return false;
		switch (tType) {
		case TargetType::Player:
			if (target->IsPlayer()) {
				return true;
				break;
			}
		case TargetType::Enemy:
			if (!target->IsPlayer()) {
				return true;
				break;
			}
		default:
			return false;
			break;
		}
	}
};

class Enemy : public Actor {
public:
	Enemy();
	Enemy(int startinghealth);
	void Action();
	void AddAction(EffectType actionAdd, int valueAdd);
	struct EnemyAction {
		EffectType actionType;
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
	void NewFight();
	Card *DrawFromLibrary();
	void MoveToDiscard(Card* c);
	void InitializeLibrary(Card **cards, int ncards);
	void ResetEnergy() { energyRemaining = maxEnergy; }
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
