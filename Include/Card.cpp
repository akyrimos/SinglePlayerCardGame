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
	filepath = "../Lib/Images/attack card.png";
	EnergyCost = 1;
	ID = 1;
	value = 6;
	ability = CardEnum::Attack;
}

Card::Card(int EnergyCost, int ID, string name) {
	this->filepath = name;
	this->EnergyCost = EnergyCost;
	this->ID = ID;
	ability = CardEnum::Undefined;
}

Card::~Card() {
}

void Card::initializeImage(float depth) {
	this->Image.Initialize(filepath, depth);
	this->Image.SetScale({ 0.2f, 0.2f });
}

void Card::Display() {
	this->Image.Display();
}

void Card::SetAction(CardEnum newAbility, int newValue) 
{
	ability = newAbility;
	value = newValue;
}

void Card::PlayCard()
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
void Card::PlayCard(Actor* target) 
{
	if (target->isPlayer()) 
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
	else if(!target->isPlayer())
	{
		switch (ability)
		{
		case CardEnum::Attack:
			cout << "Attack!";
			target->TakeDamage(this->value);
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