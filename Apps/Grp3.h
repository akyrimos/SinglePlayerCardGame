#ifndef GRP3
#define GRP3
#include "Sprite.h"
#include <stack>
#include<string> 

using namespace std;
const int MaxHandSize = 10;

enum class EffectType { Undefined = 0, Attack, Defend, Debuff, Buff, Power, NActions };
enum class TargetType { Undefined = 0, Player, Enemy, None, NActions };
class Action {
public:
	int value;
	EffectType effect;
	Action(int val, EffectType eff) :value(val), effect(eff) {};
};
class Actor : public Sprite {
public:
	int health = 10;
	int maxHealth = 10;
	int armor = 0;
	int *status = NULL;
	string message;
	void GainArmor(int value) { armor += value; }
	bool CheckifAlive() { return health > 0; }
	virtual bool IsPlayer() { return true; }
	void ChangeHealth(int healthToAdd) { if ((health += healthToAdd) > maxHealth) health = maxHealth; }
	void TakeDamage(int damage) {
		armor -= damage;
		if (armor < 0) {
			health -= abs(armor);
			RemoveArmor();
			CheckifAlive();
			message = "ouch! my health now " + to_string(health);
		}
	}
	void RemoveArmor() { armor = 0; }
};

class Card : public Sprite {
public:
	vec3 position;
	int energyCost;
	int id;
	EffectType ability;
	vector<Action> actions;
	TargetType tType;
	int value;
	Card() {
		energyCost = 1;
		value = 6;
		ability = EffectType::Attack;
		tType = TargetType::Enemy;
		Action a(6, EffectType::Attack);
		actions.push_back(a);
		actions.push_back(a);
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
		cout << "My health now: " << target->armor << endl;
		cout << cardNames[(int) ability] << endl;
		if (ValidTarget(target)) {
			if (!target->IsPlayer() && ability == EffectType::Attack)
				target->TakeDamage(value);
			if (!target->IsPlayer() && ability == EffectType::Defend) {
				//this should be played on the player
				cout << "value: " << value << endl;
				target->GainArmor(value);
				cout << "My health now: " << target->armor << endl;
			}
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
	bool IsPlayer();
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
	bool ConsumeEnergy(Card* card);
	void Draw();
	void DiscardHand();
	void Shuffle();
	void NewFight();
	Card *DrawFromLibrary();
	void MoveCardOffScreen(Card* selectedCard);
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


void ResolveAction(vector<Action> actions, Actor* user, Actor* target);
void ResolveAction(Action a, Actor* user, Actor* target);

#endif
