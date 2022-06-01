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
//class Effect {
//public:
//	int value;
//	EffectType effType;
//	Effect(int val, EffectType eff) :value(val), effType(eff) {};
//};

class Effect {
public:
	int value;
	EffectType effectType;
	Effect(int val, EffectType effType) :value(val), effectType(effType) {};
};
class Action {
public:
	string name;
	vector<Effect> effects;
	Action() :name("none"), effects(vector<Effect>{}) {};
	Action(string n, vector<Effect> effs) :name(n), effects(effs) {};
};
class CardData {
public:
	string name;
	string imageName;
	int energyCost;
	Action action;
	TargetType targetType;
	CardData(string n, string img, int cost, Action act, TargetType targ) 
		: name(n), imageName(img), energyCost(cost), action(act), targetType(targ) {};
};
class EnemyData {
public:
	string name;
	string imageName;
	int maxHP;
	vector<Action> actionsPool;
	EnemyData(string n, string img, int hp, vector<Action> pool)
		: name(n),imageName(img), maxHP(hp), actionsPool(pool) {};
};
class Actor : public Sprite {
public:
	int maxHealth = 10;
	int health = maxHealth;
	int armor = 0;
	int* status = NULL;
	int strength = 0;
	int dexterity = 0;
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
	void gainStrength() { strength += 1; }
	void gainDexterity() { dexterity += 1; }
};

class Card : public Sprite {
public:
	string name;
	string imageDir;
	vec3 position;
	int energyCost;
	//int id;
	EffectType ability;
	Action action;
	TargetType tType;
	Card() {
		energyCost = 1;
		ability = EffectType::Attack;
		tType = TargetType::Enemy;
		name = "Strike";
		action = Action("Strike", vector<Effect> {Effect(6, EffectType::Attack)});
	};
	
	Card(const CardData c) {
		name = c.name;
		energyCost = c.energyCost;
		action = c.action;
		tType = c.targetType;
		imageDir = c.imageName;
	};
	//Card(int EnergyCost, int Value, EffectType Effect, TargetType TargType) {
	//	actions.push_back(Effect(Value,Effect));
	//	this->energyCost = EnergyCost;
	//	this->ability = Effect;
	//	this->tType = TargType;
	//}
	/*Card(int energycost, vector<Effect> Actions, TargetType TargType) {
		this->energyCost = energycost;
		this->tType = TargType;
		this->action = Actions;
	}*/

	//void AddAction(int value, EffectType effect) {
	//	action.push_back(Effect(value, effect));
	//}
	/*void SetAction(EffectType newAbility, int newValue) {
		ability = newAbility;
	}*/
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
	vector<Action> actionsPool;
	Enemy();
	Enemy(EnemyData d);
	void AddAction(Action a) {actionsPool.push_back(a);}
	string printAction(EffectType);
	Action chosenAction;
	void PrepareAction();
	void ActionMessage();
	Action TakeAction();
	void ResetEnemy();
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
	void InitializeLibrary(vector<Card*> cards, int ncards);
	void AddCard(Card* card);
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

void ResolveAction(const Action act, Actor* user, Actor* target);
void ResolveEffect(const Effect e, Actor* user, Actor* target);

#endif
