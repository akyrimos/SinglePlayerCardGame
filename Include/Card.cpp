#include <glad.h>
#include <time.h>
#include <vector>
#include "VecMat.h"
#include "Card.h"
#include "CardEnum.h"
#include "Sprite.h"
#include "Character.h"
#include "../Apps/CardEnum.h"

using namespace std;
using std::string;


Card::Card(string image) {
	this->Image.Initialize(image, 0.1f);
	Name = "Default";
	Energy = 0;
	ID = 1;
	CardAction = new Action;
}
void Card::SetAction(CardEnum newAbility, int newValue) {
	CardAction->ability = newAbility;
	CardAction->value = newValue;
}
