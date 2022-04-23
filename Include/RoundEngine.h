#ifndef RoundEngine
#define RoundEngine

#include "Character.h"
#incldue "Sprite.h"
#include <glad.h>
#include <time.h>


class RoundEngine {


public:
	RoundEngine();
	~RoundEngine();

	void intializeEnemy();
	void removeStatus();
};
#endif // !RoundEngine
