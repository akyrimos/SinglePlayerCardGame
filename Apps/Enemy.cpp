#include "CardGame.h"
#include <random>

Enemy::Enemy() {
	maxHealth = 10;
	health = maxHealth;
	armor = 0;
	status = 0;
	isPlayer = false;
}

Enemy::Enemy(EnemyData d) {
	maxHealth = d.maxHP;
	health = maxHealth;
	armor = 0;
	status = 0;
	imageName = d.imageName;
	isPlayer = false;
	for (int i = 0; i < (signed)d.actionsPool.size(); i++)
		actionsPool.push_back(d.actionsPool. at(i));
}


void Enemy::PrepareAction() {
	if (!CheckifAlive()) { chosenAction = Action(); return; }
	unsigned seed = clock();
	shuffle(actionsPool.begin(), actionsPool.end(), std::default_random_engine(seed));
	chosenAction = actionsPool.at(0);
	ActionMessage();
}

void Enemy::ActionMessage() {
	for (Effect e : chosenAction.effects) {
		string type = "";
		switch (e.effectType) {
		case EffectType::Attack:
			type = "Attack ";
			break;
		case EffectType::Defend:
			type = "Defend ";
			break;
		case EffectType::Buff:
			type = "Buff ";
			break;
		case EffectType::Power:
			type = "Power ";
			break;
		case EffectType::Weaken:
			type = "Weaken ";
			break;
		default:
			type = "I dont know what im doing!";
			break;
		}
		message += type + to_string(e.value) + " ";
	}
}
Action Enemy::TakeAction() {
	if (!CheckifAlive()) chosenAction = Action();
	return chosenAction;
}

string Enemy::printAction(EffectType type) {
	string temp;
	switch (type) {
	case EffectType::Attack:
		temp = "Attack you";
		break;
	case EffectType::Defend:
		temp = "Defend myself";
		break;
	case EffectType::Buff:
		temp = "Buff myself";
		break;
	case EffectType::Power:
		temp = "Power up myself";
		break;
	case EffectType::Weaken:
		temp = "Weaken you";
		break;
	default:
		temp = "I dont know what im doing!";
		break;
	}
	return temp;
}

void Enemy::ResetEnemy() {
	maxHealth += 5;
	this->health = maxHealth;
	this->SetPosition({ 0.35f, 0.1f });
}