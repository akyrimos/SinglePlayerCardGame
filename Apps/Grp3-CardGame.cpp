// CardGame.cpp - hosts the display and runs the while loop

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "vector"
#include "Draw.h"
#include "GLXtras.h"
#include "Grp3.h"
#include "Misc.h"
#include "Sprite.h"
#include "Text.h"

// App
int winWidth = 800, winHeight = 800;
bool startScreen = true;

// Images
string dir = "../Lib/Images/";
string playCardTex = dir+"alien_slime.png", playCardMat = dir+"alien_slime.png";
string backgroundTex = dir+"fightbackground.png";
string endTurnTex = dir+"end_turn_btn.png";
string startscreenBack = dir+"backgroundStart.png";
string startButtonTex = dir+"startScreenButton.png", startButtonMat = dir+"startScreenButton.png";
string attackCardImageName = dir+"attack card.png";
string enemyImageName = dir+"alien_slime.png";
string playerImageName = dir+"YosemiteSam.tga";
string defendCardImageName = dir+"defend.png";

// Sprites
Actor player;
Enemy alien;
Card c0, c1, c2, c3, c4, c5(1, 5, EffectType::Defend, TargetType::Player), c6(1, 5, EffectType::Defend, TargetType::Player), c7(1, 5, EffectType::Defend, TargetType::Player), c8(1, 5, EffectType::Defend, TargetType::Player), c9(1, 5, EffectType::Defend, TargetType::Player);
Sprite background, playCard, endTurn, startBackground, startButton;

// Gameplay
int turnNum = 0;
Card *selectedCard = NULL;
vector<Actor *> targets;
HandManager hm;
Card *deck[] = { &c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9 };

// Display

void DisplayActor(Actor *a, vec3 color = vec3(1, 0, 0)) {
	a->Display();
	vec3 loc = vec3(a->position, 0);
	if (!a->message.empty()) {
		Text(loc, a->ptTransform, color, 20, a->message.c_str());
	}
	//health
	if (a->health > 0)
		Text(loc + vec3(0,1,0), a->ptTransform, vec3(1,0,0), 30, to_string(a->health).c_str());
	//armor
	if (a->armor > 0) 
		Text(loc + vec3(-0.2f, 1.0f, 0.0f), a->ptTransform, vec3(0.2f,1.0f,1.0f), 30, to_string(a->armor).c_str());
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
		// playCard.Display();
		endTurn.Display();
		for (int i = 0; i < (int) hm.hand.size(); i++)
			hm.hand[i]->Display();
		DisplayActor(&player, vec3(0, 0, 0));
		for (int i = 0; i < (int) targets.size(); i++)
			DisplayActor(targets[i]);
		player.Display();
		string energyUI = to_string(hm.energyRemaining) + "/" + to_string(hm.maxEnergy);
		string turnUI = to_string(turnNum);
		Text(vec3(-1, -.75, 0), background.ptTransform, vec3(1, 1, 0), 50, energyUI.c_str());
		Text(vec3(0.9, 0.9, 0), background.ptTransform, vec3(1, 1, 0), 50, turnUI.c_str());

	}
	glFlush();
}

// Gameplay
//void CardPlayer(Sprite* card, Sprite target) {
//	// helper method to play a card on a enemy
//	if (card) {
//		if (card->Intersect(target)) {
//			card->SetPosition({ -5.0f, -5.0f }); //Check if it is a valid target before doing an action(playing a card) on target
//		}
//	}
//	// before it goes null add the card to the discard pile (library)
//	card = NULL;
//}

float handXPos[10] = {-.5f, -.4f, -.3f, -.2f, -.1f, 0, .1f, .2f, .3f, .4f}, handYPos = -.75f;

float Z(int i) { return .2f+i*.05f; }

void NewHand() {
	for (int i = 0; i < hm.drawCards; i++)
		hm.Draw();
	turnNum++;
	for (int i = 0; i < (int) hm.hand.size(); i++) {
		hm.hand[i]->SetPosition(vec2(handXPos[i], handYPos));
		hm.hand[i]->z = Z(i);
	}
}

// get actions from Card, user, and target from CardGame
void ResolveAction(stack<Action> actions, Actor* user, Actor* target) {
	while (!actions.empty()) {
		//ResolveAction(actions.top(), user, target*);
		actions.pop();
	}
}
void ResolveAction(Action a, Actor* user, Actor* target) {
	switch (a.effect) {
	case EffectType::Attack:
		target->TakeDamage(a.value);
		break;
	case EffectType::Defend:
		cout << "armor";
	default:
		cout << "default";
	}
}

void RunTurn() {
	hm.DiscardHand();
	hm.ResetEnergy();
	// Enemy takes turn
	player.RemoveArmor();
	alien.RemoveArmor();
	alien.message = "";
	// tick down status effects go here
	NewHand();
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
			NewHand();
		}
		if (endTurn.Hit(ix, iy))
			RunTurn();
	}
	// Play card on target
	if (action == GLFW_RELEASE) {
		if (selectedCard)
			for (int i = 0; i < (int) targets.size(); i++) {
				Actor* target = targets[i];
				if (target->Intersect(*selectedCard)) {
					if (selectedCard->ValidTarget(target)) {
						//if(hm.ConsumeEnergy(selectedCard))
							//ResolveAction(selectedCard->actions, &player, target);
							hm.PlayCard(targets[i], selectedCard);
					}
					//hm.PlayCard(targets[i], selectedCard);

				}
			}

	}
}

//Mouse function to move the card
void MouseMove(GLFWwindow *w, double x, double y) {
	if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && selectedCard)
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
	startButton.Initialize(startButtonTex, startButtonMat, .85f);
	endTurn.Initialize(endTurnTex, .05f);
	// scale, position buttons
	startButton.SetScale({ 0.3f, 0.3f });
	startButton.SetPosition({ .10f, -.45f });
	endTurn.SetScale({ 0.2f, 0.1f });
	endTurn.SetPosition({ 0.5f, -.4f });
	// playCard.Initialize(playCardTex, playCardMat, .6f);
	// playCard.SetScale({ 0.2f, 0.2f });
	// playCard.SetPosition({ 0.5f, .0f });
	// initialize card sprites, deckLibrary
	GLuint attackCardTextureName = LoadTexture(attackCardImageName.c_str());
	GLuint defendCardTextureName = LoadTexture(defendCardImageName.c_str());
	GLuint enemyTextureName = LoadTexture(enemyImageName.c_str());
	GLuint playerTextureName = LoadTexture(playerImageName.c_str());
	int nDeckCards = sizeof(deck)/sizeof(Card *);
	for (int i = 0; i < nDeckCards; i++) {
		if (deck[i]->ability == EffectType::Attack) 
			deck[i]->Initialize(attackCardTextureName);
		if (deck[i]->ability == EffectType::Defend)
			deck[i]->Initialize(defendCardTextureName);

		deck[i]->SetScale(vec2(.2f, .2f));
	}
	hm.InitializeLibrary(deck, nDeckCards);
	hm.DiscardHand();
	hm.DiscardHand();
	hm.Shuffle();
	// initialize player sprite
	player.Initialize(playerTextureName, .7f);
	player.SetScale(vec2(.2f, .3f));
	player.SetPosition(vec2(-.6f, -.2f));
	//player.message = "Tarnation!";
	// initialize alien sprite
	alien.Initialize(enemyTextureName, .65f);
	alien.SetScale(vec2(.7f, .7f));
	alien.SetPosition({0.35f, 0.1f});
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
