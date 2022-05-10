// CardGame.cpp - hosts the display and runs the while loop

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "GLXtras.h"
#include "Misc.h"
#include "../Include/Card.h"
#include "vector"
#include "Sprite.h"
#include "Library.h"
#include "TurnManager.h"
#include "Actor.h"
#include "Enemy.h"
#include "../Include/HandManager.h"


int winWidth = 800, winHeight = 800;
Sprite background, playCard, endTurn, * selected = NULL, startBackground, start_button;
//C:/Users/onlys/Source/Repos/akyrimos/SinglePlayerCardGame
//../Lib/Images gives error for me (ryan) wont load textures
string dir = "../Lib/Images/";
string sprite1Tex = dir+"attack card.png", sprite1Mat = dir+"attack card.png";
string playCardTex = dir + "playcard.png", playCardMat = dir + "playcard.png";
string combined32 = dir+"Combined32.png"; // png, tga ok; bmp, jpg do not support 32
string backgroundTex = dir+"Outline.png";
string endTurnTex = dir + "end_turn_btn.png";
string startscreenBack = dir + "backgroundStart.png";
string startButton = dir + "startScreenButton.png", startButtonMat = dir + "startScreenButton.png";

Card card1 = Card();
Card card2 = Card();
Card card3 = Card();
Card card4 = Card();
Card card5 = Card();

Library library = Library();
HandManager hand = HandManager(&library);
Actor player = Actor();
Enemy alien = Enemy();
TurnManager turnEngine = TurnManager(&hand, &alien, &player);

vector<Sprite*> interactables;

float handXPos[10] = {-.50f, -.40f, -.30f, -.20f, -.10f, 0, .10f, .20f, .30f, .40f};
const float handYPos = -.75f;

bool startScreen = true;




// Display

void Display() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	background.Display();
	playCard.Display();
	endTurn.Display();
	card1.Display();
	glFlush();
}

//Added display function for start screen for our program
void DisplayStartScreen() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	interactables.push_back(&start_button);
	interactables.push_back(&card1.Image);
	startBackground.Display();
	start_button.Display();

	glFlush();
}

//helper method to play a card on a enemy
void CardPlayer(Sprite* card, Sprite target) {
	if (card) {
		if (card->Intersect(target)) {
			card->SetPosition({ -5.0f, -5.0f }); //Check if it is a valid target before doing an action(playing a card) on target

		}
	}
	//before it goes null add the card to the discard pile (library)
	card = NULL;
}

// Mouse

void MouseButton(GLFWwindow *w, int butn, int action, int mods) {
	double x, y;
	glfwGetCursorPos(w, &x, &y);
	y = winHeight-y; // invert y for upward-increasing screen space
	if (action == GLFW_PRESS) {
		int ix = (int)x, iy = (int)y;
		selected = NULL;
		for (Sprite* x : interactables) {
			if (x->Hit(ix, iy)) selected = x;
		}
		if (selected) {
			selected->MouseDown(vec2((float)x, (float)y));
		}
		if (selected == &start_button) {
			startScreen = false;
		}
		if (selected == &endTurn) {
			turnEngine.RunTurn();
		}
	}

	if (action == GLFW_RELEASE) {
		//startScreen = false;
		CardPlayer(selected, playCard);
		/*
		if (selected) {
			if (selected->Intersect(playCard))
				selected->SetPosition({ -5.0f, -5.0f });
		}
		selected = NULL;
		*/
	}


}

void MouseMove(GLFWwindow *w, double x, double y) {
	if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && selected)
		selected->MouseDrag(vec2((float) x, (float) (winHeight-y)));
}

void MouseWheel(GLFWwindow *w, double ignore, double spin) {
	if (selected)
		selected->MouseWheel(spin);
}

void SetHand() {
	for (int i = 0; i < hand.handSize; i++) {
		hand.hand.at(i).Image.SetPosition({ handXPos[i], handYPos }); //Attrocious... haha
	}
}
// Application

void Resize(GLFWwindow *w, int width, int height) {
	glViewport(0, 0, winWidth = width, winHeight = height);
}

int main(int ac, char** av) {
	// init app window and GL context
	glfwInit();
	GLFWwindow* w = glfwCreateWindow(winWidth, winHeight, "Destroy the Aliens", NULL, NULL);
	glfwSetWindowPos(w, 100, 100);
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// read background, foreground, and mat textures
	//Card atk = Card(sprite1Tex);

	startBackground.Initialize(startscreenBack, "", 10, .7f);
	start_button.Initialize(startButton, startButtonMat, 11, .25f);
	start_button.SetScale({ 0.3f, 0.3f });
	start_button.SetPosition({ .10f, -.45f });

	library.Add(card1);
	library.Add(card2);
	library.Add(card3);
	library.Add(card4);
	library.Add(card5);

	background.Initialize(backgroundTex, "", 0, .7f);
	playCard.Initialize(playCardTex, playCardMat, 4, .6f);
	endTurn.Initialize(endTurnTex, "", 5, .1f);

	card1.initializeImage(.1f);
	playCard.SetScale({ 0.2f, 0.2f });
	playCard.SetPosition({ 0.5f, .0f });
	endTurn.SetScale({ 0.2f, 0.1f });
	endTurn.SetPosition({ 0.5f, -.4f });

	// callbacks
	glfwSetMouseButtonCallback(w, MouseButton);
	glfwSetCursorPosCallback(w, MouseMove);
	//glfwSetScrollCallback(w, MouseWheel);
	glfwSetWindowSizeCallback(w, Resize);
	// event loop
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(w)) {
		
		if (startScreen) {
			DisplayStartScreen();
			glfwSwapBuffers(w);
			glfwPollEvents();
		}
		else {
			Display();
			glfwSwapBuffers(w);
			glfwPollEvents();

		}
	}
	// terminate
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	background.Release();
	start_button.Release();
	startBackground.Release();
	playCard.Release();
	endTurn.Release();
	glfwDestroyWindow(w);
	glfwTerminate();
}
