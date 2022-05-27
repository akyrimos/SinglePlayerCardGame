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