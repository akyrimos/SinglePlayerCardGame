#ifndef Enemy
#define Enemy
#include "Sprite.h"
#include "Character.h"

using namespace std;

class Enemy: Character {
private:
	int health;
	int temparmor;
	int *status;
	Sprite Image;

public:
	Enemy();
	Enemy(const Enemy& other);
	Enemy& operator=(const Enemy& rhs);
	~Enemy();
	bool CheckifAlive();
	void takeDamagefromCard(int);
	void dissapear();

};
#endif