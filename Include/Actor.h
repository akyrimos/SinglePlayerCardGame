#ifndef ACTOR
#define ACTOR
#include "Sprite.h"
using namespace std;

class Actor {
protected:
	int actorId;
	int health;
	int maxHealth;
	int tempArmor;
	int *status;
	static int nextId;

public:
	Actor();
	Actor(const Actor& other);
	Actor& operator=(const Actor& rhs);
	~Actor();
	Sprite image;
	void ChangeHealth(int healthToAdd);
	void TakeDamage(int damage);
	bool CheckifAlive();
	bool IsPlayer();
	void RemoveArmor();
};
#endif