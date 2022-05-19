#pragma once
#ifndef ENEMY
#define ENEMY
#include "../Include/Actor.h"
#include "../Include/CardEnum.h"
#include <vector>

class Enemy : public Actor
{
public:
	Enemy();
	Enemy(int startinghealth, string name);
	~Enemy();

	void enemyAction();
	void IntializeEnemy(float depth);
	void SetPositionEnemy(float x, float y);
	void AddAction(CardEnum actionAdd, int valueAdd);

private:
	string filepath;
	void gainArmor();

	struct EnemyAction {
		CardEnum actionType;
		int actionValue;
	};

	vector<EnemyAction> ActionVec;

};


#endif
