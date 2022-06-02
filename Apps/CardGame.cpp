// CardGame.cpp - hosts the display and runs the while loop

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Draw.h"
#include "GLXtras.h"
#include "CardGame.h"
#include "Misc.h"
#include "Sprite.h"
#include "Text.h"

// App
int winWidth = 1200, winHeight = 800;
bool startScreen = true;
bool rewardScreen = false;

// Images
string dir = "../Lib/Images/";
//string playCardTex = dir+"alien_slime.png", playCardMat = dir+"alien_slime.png"
string backgroundTex = dir+"Atmosphere.png";
string endTurnTex = dir+"end_turn_btn.png";
string startscreenBack = dir+"backgroundStart.png";
string startButtonTex = dir + "startScreenButton.png";
string attackCardImageName = dir+"attack.png"; //attack.png

//	Card Images
string strikeDir = dir + "strike.png";
string blockDir = dir + "block.png";

//	Actor Images
string playerDir = dir + "Player.png";
string chompDir = dir + "Chomp.png";
string enemyImageName = dir+"alien_slime.png";

string defendCardImageName = dir+"defend.png";
string strengthRewardTex = dir + "strengthReward.png";
string healthRewardTex = dir + "chargeReward.png";
string protectionRewardTex = dir + "protectionReward.png";


// Action definitions
Action a_strike("Strike", vector<Effect>{ Effect(6, EffectType::Attack) });
Action a_block("Block", vector<Effect>{ Effect(5, EffectType::Defend) });
Action a_doubleStrike("Double Strike", vector<Effect>{ Effect(6, EffectType::Attack), Effect(6, EffectType::Attack) });
Action a_bigStrike("Big Strike", vector<Effect>{ Effect(10, EffectType::Attack) });

// CardData definitions
CardData strike(a_strike.name, strikeDir, 1, a_strike, TargetType::Enemy);
CardData block(a_block.name, blockDir, 1, a_block, TargetType::Player);

//EnemyData definitions
vector<Action> testMovePool(vector<Action> {a_bigStrike, a_block, a_doubleStrike});
EnemyData test("Chomp",chompDir, 10, testMovePool);
// Sprites
Actor player("Player", playerDir, 20);
Enemy alien(test);
Card c0(strike), c1(strike), c2(strike), c3(strike), c4(strike),
c5(block), c6(block), c7(block), c8(block), c9(block);
Sprite background, playCard, endTurn, startBackground, startButton, strengthReward,healthReward,protectionReward;

// Card Positions
float handXPos[5] = { -.5f, -.3f, -.1f, .1f, .3f }, handYPos = -.75f;

float Z(int i) { return .2f + i * .05f; }
// Gameplay
int turnNum = 0;
Card* selectedCard = NULL;
vector<Actor *> targets;
HandManager hm;
//Card* deck[] = { &c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9 };
vector<Card*> deck = { &c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9 };
// Display

void DisplayActor(Actor *a, vec3 color = vec3(1, 0, 0)) {
	a->Display();
	vec3 loc = vec3(a->position, 0);
	if (!a->message.empty()) {
		Text(loc + vec3(-0.75f,0.9f,0), a->ptTransform, color, 20, a->message.c_str());
	}
	//health
	if (a->health > 0)
		Text(loc + vec3(0,1,0), a->ptTransform, vec3(1,0,0), 30, to_string(a->health).c_str());
	//armor
	if (a->armor > 0) 
		Text(loc + vec3(-0.5f, 1.0f, 0.0f), a->ptTransform, vec3(0.2f,1.0f,1.0f), 30, to_string(a->armor).c_str());
}
void DisplayRewards() {
	strengthReward.Display();
	healthReward.Display();
	protectionReward.Display();
}
void Display() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	if (startScreen) {
		startBackground.Display();
		startButton.Display();
	}
	else {
		background.Display();
		endTurn.Display();
		for (int i = 0; i < (int) hm.hand.size(); i++)
			hm.hand[i]->Display();
		for (int i = 0; i < (int)targets.size(); i++)
			if (targets[i]->CheckifAlive())
				DisplayActor(targets[i]);
			else {
				targets[i]->SetPosition(vec2(-5.0f, -5.0f));
				if (targets[i]->IsPlayer()) {
					//defeat
				}
				else {
					if(rewardScreen == true)
						DisplayRewards();
					//rewardChoice = false;
					//targets[i]->ChangeHealth(100);
					//display reward screen
					//make enemy stronger
					//intialize new fight
				}
			}

		string energyUI = to_string(hm.energyRemaining) + "/" + to_string(hm.maxEnergy);
		string turnUI = "Turn " + to_string(turnNum);
		string deckUI = "Deck: " + to_string(hm.deckLibrary.size());
		string discardUI = "Discard: "+ to_string(hm.discardPile.size());
		Text(vec3(-.9f, -.75f, .0f), background.ptTransform, vec3(1, 1, 0), 50, energyUI.c_str());
		Text(vec3(0.7f, 0.9f, .0f), background.ptTransform, vec3(1, 1, 0), 30, turnUI.c_str());
		Text(vec3(-.96f, -.95f, .0f), background.ptTransform, vec3(1, 0.5, 0), 30, deckUI.c_str());
		Text(vec3(.6f, -.95f, .0f), background.ptTransform, vec3(1, 0.5, 0), 30, discardUI.c_str());
	}
	glFlush();
}


void NewHand() {
	for (int i = 0; i < hm.drawCards; i++)
		hm.Draw();
	turnNum++;
	for (int i = 0; i < (int) hm.hand.size(); i++) {
		hm.hand[i]->SetPosition(vec2(handXPos[i], handYPos));
		hm.hand[i]->z = Z(i);
	}
}
void StartTurn() {
	alien.PrepareAction();
	NewHand();
}
void ResolveAction(const Action act, Actor* user, Actor* target) {
	for (Effect e : act.effects) {
		ResolveEffect(e, user, target);
	}
}
void ResolveEffect(const Effect e, Actor* user, Actor* target) {
	switch (e.effectType) {
	case EffectType::Attack:
		target->TakeDamage(e.value + user->strength);
		cout << "Attack " << e.value + user->strength << endl;
		user->totalDamage += e.value + user->strength;
		break;
	case EffectType::Defend:
		user->GainArmor(e.value + user->dexterity);
		cout << "Defend " << e.value + user->dexterity << endl;
		user->totalBlock += e.value + user->dexterity;
		break;
	default:
		cout << "default";
	}

	if (!target->CheckifAlive()) {
		if (target->IsPlayer()) {
			cout << "A loser is you" << endl;
		}
		else {
			rewardScreen = true;
			cout << "A winner is you" << endl;
		}
	}
}

void RunTurn() {
	hm.DiscardHand();
	hm.ResetEnergy();
	// Enemy takes turn
	alien.RemoveArmor();
	
	ResolveAction(alien.TakeAction(), &alien, &player);

	player.RemoveArmor();
	alien.message = "";
	// tick down status effects go here
	StartTurn();
}

void NewRound() {
	hm.DiscardHand();
	hm.ResetEnergy();
	alien.RemoveArmor();
	alien.ResetEnemy();
	player.RemoveArmor();
	player.totalrounds += 1;
	alien.totalrounds += 1;
	alien.message = "";
	StartTurn();
}

// Mouse with cards playing on enemy and clicking buttons

void MouseButton(GLFWwindow *w, int butn, int action, int mods) {
	double x, y;
	glfwGetCursorPos(w, &x, &y);
	y = winHeight-y; // invert y for upward-increasing screen space
	int ix = (int) x, iy = (int) y;
	if (action == GLFW_PRESS) {
		selectedCard = NULL;
		for (int i = 0; i < (int) hm.hand.size(); i++) {
			Card *c = hm.hand[i];
			if (c->Hit(ix, iy))
				selectedCard = c;
		}
		if (selectedCard)
			selectedCard->MouseDown(vec2((float)x, (float)y));
		if (startButton.Hit(ix, iy)) {
			startScreen = false;
			StartTurn();
		}
		if (endTurn.Hit(ix, iy))
			RunTurn();

		//might have to do with strength reward positioning. It is on top of the player sprite
		//I think this is the only reward that gets executed after every turn.
		if (rewardScreen == true) {
			if (strengthReward.Hit(ix, iy))
				player.gainStrength();
			else if (protectionReward.Hit(ix, iy))
				player.gainDexterity();
			else if (healthReward.Hit(ix, iy))
				player.ChangeHealth(100);
			rewardScreen = false;
			NewRound();
		}


	}
	// Play card on target
	if (action == GLFW_RELEASE) {
		if (selectedCard)
			for (int i = 0; i < (int) targets.size(); i++) {
				Actor* target = targets[i];
				if (target->Intersect(*selectedCard)) {
					if (selectedCard->ValidTarget(target)) {
						if (hm.ConsumeEnergy(selectedCard)) {
							ResolveAction(selectedCard->action, &player, target);
							hm.DiscardCard(selectedCard);
						}
					}
				}
			}
	}
}

//Mouse function to move the card
void MouseMove(GLFWwindow *w, double x, double y) {
	if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && selectedCard && player.CheckifAlive())
		selectedCard->MouseDrag(vec2((float) x, (float) (winHeight-y)));
}

// Application

void Resize(GLFWwindow *w, int width, int height) {
	glViewport(0, 0, winWidth = width, winHeight = height);
}

int main(int ac, char** av) {
	// init app window and GL context
	glfwInit();
	GLFWwindow *w = glfwCreateWindow(winWidth, winHeight, "Destroy the Aliens", NULL, NULL);
	glfwSetWindowPos(w, 100, 100);
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// initialize background and button sprites
	background.Initialize(backgroundTex, .9f);
	startBackground.Initialize(startscreenBack, .9f);
	startButton.Initialize(startButtonTex, .85f);
	endTurn.Initialize(endTurnTex, .05f);
	//intialize rewards
	strengthReward.Initialize(strengthRewardTex, .04f);
	healthReward.Initialize(healthRewardTex, .03f);
	protectionReward.Initialize(protectionRewardTex, .02f);

	// scale, position buttons
	startButton.SetScale({ 0.3f, 0.2f });
	startButton.SetPosition({ .10f, -.45f });
	endTurn.SetScale({ 0.2f, 0.1f });
	endTurn.SetPosition({ 0.5f, -.4f });
	strengthReward.SetScale({ .2f,.3f });
	strengthReward.SetPosition({ -.35f,.2f });
	healthReward.SetScale({ .2f,.3f });
	healthReward.SetPosition({.1f,.2f});
	protectionReward.SetScale({ .2f,.3f });
	protectionReward.SetPosition({ .55f,.2f });
	


	// initialize card sprites, deckLibrary

	//GLuint attackCardTextureName = LoadTexture(attackCardImageName.c_str());
	//GLuint defendCardTextureName = LoadTexture(defendCardImageName.c_str());
	//GLuint enemyTextureName = LoadTexture(enemyImageName.c_str());
	//GLuint playerTextureName = LoadTexture(playerImageName.c_str());
	int nDeckCards = deck.size();//sizeof(deck)/sizeof(Card *);
	for (int i = 0; i < nDeckCards; i++) {
		string dir = deck[i]->imageDir;
		deck[i]->Initialize(dir);
		deck[i]->SetScale(vec2(.2f, .3f));
	}
	hm.InitializeLibrary(deck, nDeckCards);
	hm.DiscardHand();
	hm.DiscardHand();
	hm.Shuffle();
	// initialize player sprite
	player.Initialize(player.imageName, .7f);
	player.SetScale(vec2(.2f, .3f));
	player.SetPosition(vec2(-.6f, 0.1f));
	// initialize alien sprite
	alien.Initialize(alien.imageName, .65f);
	alien.SetScale(vec2(.3f, .3f));
	alien.SetPosition({0.35f, 0.1f});
	//push actors into targets
	targets.push_back(&player);
	targets.push_back(&alien);

	// callbacks
	glfwSetMouseButtonCallback(w, MouseButton);
	glfwSetCursorPosCallback(w, MouseMove);
	glfwSetWindowSizeCallback(w, Resize);
	// event loop
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(w)) {
		Display();
		glfwSwapBuffers(w);
		glfwPollEvents();
	}
	// terminate
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwDestroyWindow(w);
	glfwTerminate();
}
