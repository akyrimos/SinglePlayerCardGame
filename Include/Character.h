#ifndef CHARACTER
#define CHARACTER
#include "Sprite.h"
using namespace std;

class Character {
private:
	int health;
	int temparmor;
	//int *buff;
public:
	bool CheckifAlive();
};
#endif