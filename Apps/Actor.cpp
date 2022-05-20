#include "../Include/Actor.h"
//	public

using namespace std;

Actor::Actor()
{
	actorId = nextId;
	maxHealth = 10;
	health = maxHealth;
	tempArmor = 0;
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

bool Actor::IsPlayer() 
{
	return false;
}

void Actor::ChangeHealth(int healthToAdd) {
	if (health + healthToAdd > maxHealth) {
		health = maxHealth;
	}
	else {
		health += healthToAdd;
	}
}

void Actor::TakeDamage(int damage) {
	tempArmor -= damage;
	if (tempArmor < 0) {
		health -= abs(tempArmor);
		RemoveArmor();
		CheckifAlive();
		cout << "ouch! my hp is " << health << endl;
	}
}

void Actor::RemoveArmor() {
	tempArmor = 0;
}

int Actor::nextId = 0;