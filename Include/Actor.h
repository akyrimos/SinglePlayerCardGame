#ifndef ACTOR
#define ACTOR
#include "Sprite.h"
using namespace std;

class Actor {
private:
	int ActorID;
	int health;
	int maxHealth;
	int tempArmor;
	int *status;
	Sprite Image;
	static int next_id;

public:
	Actor();
	Actor(const Actor& other);
	Actor& operator=(const Actor& rhs);
	~Actor();

	void ChangeHealth(int healthToAdd);
	void TakeDamage(int damage);
	bool CheckifAlive();
	bool isPlayer();
	void RemoveArmor();
};
#endif