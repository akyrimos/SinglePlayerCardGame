#include "../Include/Character.h"
//	public

Character::Character()
{

}

Character::Character(const Character& other)
{
}

Character& Character::operator=(const Character& rhs)
{
	// TODO: insert return statement here
	Character temp = rhs;
	return temp;
}

Character::~Character()
{
}

bool Character::CheckifAlive()
{
	return false;
}
