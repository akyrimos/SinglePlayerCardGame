#include <glad.h>
#include <time.h>
#include <vector>
#include "VecMat.h"
#include "Card.h"
#include "CardEnum.h"
#include "Sprite.h"
#include "Character.h"
#include "CardEnum.h"

using namespace std;
using std::string;


Card::Card(string image) 
{
	this->Image.Initialize(image, 0.1f);
	Name = "Default";
	Energy = 0;
	ID = 1;
	CardAction = new Action;
}

Card::~Card() {
	Image.Release();
	delete CardAction;
}

void Card::SetAction(CardEnum newAbility, int newValue) 
{
	CardAction->ability = newAbility;
	CardAction->value = newValue;
}

void Card::PlayCard(Character target) 
{
	if (target.isPlayer()) 
	{
		switch (CardAction->ability)
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
		switch (CardAction->ability)
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