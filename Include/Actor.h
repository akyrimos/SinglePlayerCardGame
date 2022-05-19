#ifndef ACTOR
#define ACTOR
#include "Sprite.h"
using namespace std;

class Actor {
protected:
	int ActorID;
	int health;
	int maxHealth;
	int tempArmor;
	int *status;
	static int next_id;

public:
	Actor();
	Actor(const Actor& other);
	Actor& operator=(const Actor& rhs);
	~Actor();
	Sprite Image;
	void ChangeHealth(int healthToAdd);
	void TakeDamage(int damage);
	bool CheckifAlive();
	bool isPlayer();
	void RemoveArmor();
};
#endif