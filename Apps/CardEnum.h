
using namespace std;

class CardEnum {
	enum cardAbility { Attack = 5, Defend = 10, Debuff = 15, Buff = 20, Power = 25, Undefined =0,};

	/**
	* TODO: set up switch case for getAbility
	* TODO: create setAbility, maybe in Card class? 
	**/
	CardEnum::cardAbility getAbility(CardEnum::cardAbility a) {
		return Attack;
	}
};