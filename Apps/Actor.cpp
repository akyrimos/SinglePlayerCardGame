#include "../Include/Actor.h"
//	public

using namespace std;

Actor::Actor()
{
	ActorID = next_id;
	maxHealth = 10;
	health = maxHealth;
	temparmor = 0;
	status = 0;


}

Actor::Actor(const Actor& other)
{
}

Actor& Actor::operator=(const Actor& rhs)
{
	// TODO: insert return statement here
	Actor temp = rhs;
	return temp;
}

Actor::~Actor()
{
}

bool Actor::CheckifAlive()
{
	if (health > 0) 
	{
		return true;
	}
	return false;
}

bool Actor::isPlayer() 
{
	return false;
}

int Actor::next_id = 0;