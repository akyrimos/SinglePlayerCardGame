#ifndef ACTOR
#define ACTOR
#include "Sprite.h"
using namespace std;

class Actor {
private:
	int ActorID;
	int health;
	int maxHealth;
	int temparmor;
	int *status;
	Sprite Image;
	static int next_id;

public:
	Actor();
	Actor(const Actor& other);
	Actor& operator=(const Actor& rhs);
	~Actor();

	void changeHealth(int healthToAdd);
	void takeDamage(int damage);
	bool CheckifAlive();
	bool isPlayer();
};
#endif