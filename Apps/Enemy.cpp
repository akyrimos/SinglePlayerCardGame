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

void Enemy::Action() {
//	random_shuffle(ActionVec.begin(), ActionVec.end());
	// EnemyAction chosenAction{};
	// chosenAction.actionType = ActionVec.at(0).actionType;
	// chosenAction.actionValue = ActionVec.at(0).actionValue;
	// return chosenAction;

}

void Enemy::AddAction(EffectType actionAdd, int valueAdd) {
	actions.push_back({ actionAdd, valueAdd });
}
