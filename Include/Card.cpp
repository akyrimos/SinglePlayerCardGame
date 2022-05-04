#include <glad.h>
#include <time.h>
#include <vector>
#include "VecMat.h"
#include "Card.h"
#include "CardEnum.h"
#include "Sprite.h"
#include "Actor.h"
#include "CardEnum.h"


using namespace std;
using std::string;

Card::Card() {
	
}
Card::Card(string image) 
{
	this->Image.Initialize(image, 0.3f);
	this->Image.SetScale({ 0.2f, 0.2f });
	Name = "Default";
	EnergyCost = 0;
	ID = 1;
	ability = CardEnum::Undefined;
	value = 0;
}

Card::~Card() {
	Image.Release();
}

void Card::SetAction(CardEnum newAbility, int newValue) 
{
	ability = newAbility;
	value = newValue;
}

void Card::PlayCard(Actor target) 
{
	if (target.isPlayer()) 
	{
		switch (ability)
		{
		case CardEnum::Defend:
			cout << "Defend!";
			break;
		case CardEnum::Buff:
			cout << "Buff!";
			break;
		case CardEnum::Power:
			cout << "Power!";
			break;
		default:
			cout << "Invalid Target!";
			break;
		}
	}
	else if(!target.isPlayer())
	{
		switch (ability)
		{
		case CardEnum::Attack:
			cout << "Attack!";
			break;
		case CardEnum::Debuff:
			cout << "Debuff!";
			break;
		default:
			cout << "Invalid Target!";
			break;
		}
	}

}