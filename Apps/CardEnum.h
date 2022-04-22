#ifndef CARDENUM
#define CARDENUM

using namespace std;

class CardEnum {
	enum cardAbility { Attack = 5, Defend = 10, Debuff = 15, Buff = 20, Power = 25, Undefined = 0,};

	cardAbility ability;

	cardAbility getAbility() {
		return ability;
	}

	void setAbility(cardAbility newAbility) {
		ability = newAbility;
	}

	

};
#endif // !CARDENUM
