#include "CardGame.h"
#include <random>

Enemy::Enemy() {
	maxHealth = 10;
	health = maxHealth;
	armor = 0;
	status = 0;
}

Enemy::Enemy(EnemyData d) {
	maxHealth = d.maxHP;
	health = maxHealth;
	armor = 0;
	status = 0;
	imageName = d.imageName;
	for (int i = 0; i < d.actionsPool.size(); i++)
		actionsPool.push_back(d.actionsPool.at(i));

}

bool Enemy::IsPlayer(){
	return false;
}

vector<Action> Enemy::TakeAction() {
	unsigned seed = clock();
	shuffle(actionsPool.begin(), actionsPool.end(), std::default_random_engine(seed));
	//	random_shuffle(ActionVec.begin(), ActionVec.end());
	vector<Action> chosenAction = actionsPool.at(0);
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