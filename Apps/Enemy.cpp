#include "CardGame.h"
#include <random>

Enemy::Enemy() {
	maxHealth = 10;
	health = maxHealth;
	armor = 0;
	status = 0;
}

Enemy::Enemy(int startinghealth) {
	maxHealth = startinghealth;
	health = maxHealth;
	armor = 0;
	status = 0;
}

bool Enemy::IsPlayer(){
	return false;
}


void Enemy::AddAction(EffectType actionAdd, int valueAdd) {
	actions.push_back({ actionAdd, valueAdd });
}

Enemy::EnemyAction Enemy::Action() {
	unsigned seed = clock();
	shuffle(actions.begin(), actions.end(), std::default_random_engine(seed));
	//	random_shuffle(ActionVec.begin(), ActionVec.end());
	EnemyAction chosenAction{};
	chosenAction.actionType = actions.at(0).actionType;
	chosenAction.actionValue = actions.at(0).actionValue;
	
	return chosenAction;
}