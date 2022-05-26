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

Action Enemy::TakeAction() {
	unsigned seed = clock();
	shuffle(enemyActions.begin(), enemyActions.end(), std::default_random_engine(seed));
	//	random_shuffle(ActionVec.begin(), ActionVec.end());
	Action chosenAction(enemyActions.at(0).value, enemyActions.at(0).effect);
	
	return chosenAction;
}