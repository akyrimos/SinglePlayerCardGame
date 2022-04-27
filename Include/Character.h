#ifndef CHARACTER
#define CHARACTER
#include "Sprite.h"
using namespace std;

class Character {
private:
	int characterID;
	int health;
	int maxHealth;
	int temparmor;
	int *status;
	Sprite Image;

public:
	Character();
	Character(const Character& other);
	Character& operator=(const Character& rhs);
	~Character();
	bool CheckifAlive();
	bool isPlayer();
};
#endif