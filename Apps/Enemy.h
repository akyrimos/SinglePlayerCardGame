#pragma once
#ifndef ENEMY
#define ENEMY
#include "../Include/Actor.h"
#include "../Include/CardEnum.h"

class Enemy : public Actor
{
public:
	Enemy();
	Enemy(int startinghealth, string name, int ActionArraySize);
	~Enemy();

	void enemyAction();
	void IntializeEnemy(float depth);
	void SetPositionEnemy(float x, float y);

private:
	string filepath;
	void gainArmor();

	struct EnemyAction {
		CardEnum actionType;
		int actionValue;
	};

	EnemyAction ActionArray[];
};


#endif
