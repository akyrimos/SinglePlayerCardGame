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
	energyCost = 1;
	id = 1;
	value = 6;
	ability = CardEnum::Attack;
}

Card::Card(int EnergyCost, int ID, string name) {
	this->filepath = name;
	this->energyCost = EnergyCost;
	this->id = ID;
	ability = CardEnum::Undefined;
}

Card::~Card() {
}

void Card::InitializeImage(float depth) {
	this->image.Initialize(filepath, depth);
	this->image.SetScale({ 0.2f, 0.2f });
}

void Card::Display() {
	this->image.Display();
}

void Card::SetAction(CardEnum newAbility, int newValue) 
{
	ability = newAbility;
	value = newValue;
}

void Card::PlayCard(Actor* target) 
{
	if (target->IsPlayer()) 
	{
		switch (ability)
		{
		case CardEnum::Defend:
			cout << "Defend!" << endl;
			break;
		case CardEnum::Buff:
			cout << "Buff!" << endl;
			break;
		case CardEnum::Power:
			cout << "Power!" << endl;
			break;
		default:
			cout << "Invalid Target!" << endl;
			break;
		}
	}
	else if(!target->IsPlayer())
	{
		switch (ability)
		{
		case CardEnum::Attack:
			cout << "Attack!" << endl;
			target->TakeDamage(this->value);
			break;
		case CardEnum::Debuff:
			cout << "Debuff!" << endl;
			break;
		default:
			cout << "Invalid Target!" << endl;
			break;
		}
	}

}