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


Action Enemy::TakeAction() {
	unsigned seed = clock();
	shuffle(actionsPool.begin(), actionsPool.end(), std::default_random_engine(seed));
	//	random_shuffle(ActionVec.begin(), ActionVec.end());
	Action chosenAction = actionsPool.at(0);
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