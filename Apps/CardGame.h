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
	string name;
	string imageName;
	int energyCost;
	vector<Action> actions;
	TargetType targetType;
	CardData(string n, string img, int cost, vector<Action> act, TargetType targ) 
		: name(n), imageName(img), energyCost(cost), actions(act), targetType(targ) {};
};
class EnemyData {
public:
	string name;
	string imageName;
	int maxHP;
	vector<vector<Action>> actionsPool;
	EnemyData(string n, string img, int hp, vector<vector<Action>> pool)
		: name(n),imageName(img), maxHP(hp), actionsPool(pool) {};
};
class Actor : public Sprite {
public:
	int maxHealth = 10;
	int health = maxHealth;
	int armor = 0;
	int* status = NULL;
	string name;
	string imageName;
	string message;
	bool isPlayer = true;
	Actor() {};
	Actor(string n, string img, int hp):name(n),imageName(img), maxHealth(hp),health(maxHealth){};
	void GainArmor(int value) { armor += value; }
	bool CheckifAlive() { return health > 0; }
	bool IsPlayer() { return isPlayer; }
	void ChangeHealth(int healthToAdd) { if ((health += healthToAdd) > maxHealth) health = maxHealth; }
	void TakeDamage(int damage) {
		armor -= damage;
		if (armor < 0) {
			health -= abs(armor);
			RemoveArmor();
			CheckifAlive();
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
	vector<vector<Action>> actionsPool;
	Enemy();
	Enemy(EnemyData d);
	void AddAction(vector<Action> a) {actionsPool.push_back(a);}
	string printAction(EffectType);
	vector<Action> TakeAction();
};

class HandManager {
public:
	HandManager();
	bool ConsumeEnergy(Card* card);
	void DiscardCard(Card* c);
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
