#ifndef GRP3
#define GRP3
#include "Sprite.h"
#include <stack>
#include <string> 
#include <array>

using namespace std;
const int MaxHandSize = 10;

enum class EffectType { Undefined = 0, Attack, Defend, Weaken, Buff, Power, NActions };
enum class TargetType { Undefined = 0, Player, Enemy, None, NActions };
class Action {
public:
	int value;
	EffectType effect;
	Action(int val, EffectType eff) :value(val), effect(eff) {};
};
class CardData {
public:
	string imageName;
	int energyCost;
	vector<Action> actions;
	TargetType targetType;
	CardData(string n, int cost, vector<Action> act, TargetType targ) : imageName(n), energyCost(cost), actions(act), targetType(targ) {};
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
	string imageName;
	vec3 position;
	int energyCost;
	//int id;
	EffectType ability;
	vector<Action> actions;
	TargetType tType;
	Card() {
		energyCost = 1;
		ability = EffectType::Attack;
		tType = TargetType::Enemy;
		actions = { Action(6, EffectType::Attack) };
	}
	Card(const CardData c) {
		energyCost = c.energyCost;
		actions = c.actions;
		tType = c.targetType;
		imageName = c.imageName;
	}
	Card(int EnergyCost, int Value, EffectType Effect, TargetType TargType) {
		actions.push_back(Action(Value,Effect));
		this->energyCost = EnergyCost;
		this->ability = Effect;
		this->tType = TargType;
	}
	Card(int energycost, vector<Action> Actions, TargetType TargType) {
		this->energyCost = energycost;
		this->tType = TargType;
		this->actions = Actions;
	}

	void AddAction(int value, EffectType effect) {
		actions.push_back(Action(value, effect));
	}
	void SetAction(EffectType newAbility, int newValue) {
		ability = newAbility;
	}
	//void PlayCard(Actor* target) {

	//	const char *cardNames[] = { "Undefined", "Attack", "Defend", "Debuff", "Buff", "Power" };
	//	cout << "My health now: " << target->armor << endl;
	//	cout << cardNames[(int) ability] << endl;
	//	if (ValidTarget(target)) {
	//		if (!target->IsPlayer() && ability == EffectType::Attack)
	//			target->TakeDamage(value);
	//		if (!target->IsPlayer() && ability == EffectType::Defend) {
	//			//this should be played on the player
	//			cout << "value: " << value << endl;
	//			target->GainArmor(value);
	//			cout << "My health now: " << target->armor << endl;
	//		}
	//	}
	//}
	bool ValidTarget(Actor* target) {
		if (!target) return false;
		switch (tType) {
		case TargetType::Player:
			if (target->IsPlayer()) {
				return true;
				
			}
			break;
		case TargetType::Enemy:
			if (!target->IsPlayer()) {
				return true;
			}
			break;

		default:
			return false;
			break;
		}
		return false;
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


void ResolveAction(const vector<Action> actions, Actor* user, Actor* target);
void ResolveAction(const Action a, Actor* user, Actor* target);

#endif
