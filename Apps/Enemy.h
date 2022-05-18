#pragma once
#ifndef ENEMY
#define ENEMY
#include "../Include/Actor.h"

class Enemy : public Actor
{
public:
	Enemy();
	Enemy(int startinghealth, string name);
	~Enemy();

	void enemyAction();
	void IntializeEnemy(float depth);
	void SetPositionEnemy(float x, float y);

private:
	string filepath;
	void gainArmor();
};


#endif
