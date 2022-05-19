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

Enemy::Enemy(int startinghealth, string name, int ActionArraySize) {
	ActorID = next_id;
	maxHealth = startinghealth;
	health = maxHealth;
	tempArmor = 0;
	status = 0;
	filepath = name;
	ActionArray[ActionArraySize];
}

void Enemy::IntializeEnemy(float depth) {
	this->Image.Initialize(filepath, depth);
	this->Image.SetScale({ .2f,.2f });
	
}

void Enemy::SetPositionEnemy(float x, float y) {
	this->Image.SetPosition({ x,y });
}

void Enemy::gainArmor() {
	tempArmor = 10;
}

void Enemy::enemyAction() {
	gainArmor();
}

Enemy::~Enemy() {

}