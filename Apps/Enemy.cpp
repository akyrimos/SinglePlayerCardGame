#include "Enemy.h"

using namespace std;

Enemy::Enemy() {
	ActorID = next_id;
	maxHealth = 10;
	health = maxHealth;
	tempArmor = 0;
	status = 0;
	filepath = "../Lib/Images/alien_slime.png";
}

Enemy::Enemy(int startinghealth, string name) {
	ActorID = next_id;
	maxHealth = startinghealth;
	health = maxHealth;
	tempArmor = 0;
	status = 0;
	filepath = name;
}

void Enemy::IntializeEnemy(float depth) {
	this->Image.Initialize(filepath, filepath, depth);
	this->Image.SetScale({ .2f,.2f });
	
}

void Enemy::SetPositionEnemy(float x, float y) {
	this->Image.SetPosition({ x,y });
}

void Enemy::gainArmor() {
	tempArmor = 10;
}

void Enemy::Display() {
	this->Image.Display();
}

void Enemy::enemyAction() {
	gainArmor();
}

Enemy::~Enemy() {

}

void Enemy::AddAction(CardEnum actionAdd, int valueAdd) {
	EnemyAction toAdd;
	toAdd.actionType = actionAdd;
	toAdd.actionValue = valueAdd;
	ActionVec.push_back(toAdd);
}