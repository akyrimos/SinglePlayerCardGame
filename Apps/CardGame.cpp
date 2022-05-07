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
Sprite background, sprite1, sprite2, sprite3, playCard, * selected = NULL, startBackground, start_button;
//C:/Users/onlys/Source/Repos/akyrimos/SinglePlayerCardGame
//../Lib/Images gives error for me (ryan) wont load textures
string dir = "../Lib/Images/";
string sprite1Tex = dir+"attack card.png", sprite1Mat = dir+"attack card.png";
string playCardTex = dir + "playcard.png", playCardMat = dir + "playcard.png";
string combined32 = dir+"Combined32.png"; // png, tga ok; bmp, jpg do not support 32
string backgroundTex = dir+"Outline.png";

Card temp = Card();
Library library = Library();
HandManager hand = HandManager(&library);
Actor player = Actor();
Enemy alien = Enemy();
TurnManager turnEngine = TurnManager(&hand, &alien, &player);

vector<Sprite*> interactables;
string startscreenBack = dir+"backgroundStart.png";
string startButton = dir + "startScreenButton.png", startButtonMat = dir + "startScreenButton.png";


bool startScreen = true;




// Display

void Display() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	background.Display();
	//sprite1.Display();
	//sprite2.Display();
	//sprite3.Display();
	playCard.Display();
	glFlush();
}

//Added display function for start screen for our program
void DisplayStartScreen() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	interactables.push_back(&start_button);
	interactables.push_back(&temp.Image);
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
		if (selected)
			selected->MouseDown(vec2((float) x, (float) y));
		if(selected == &start_button)
			startScreen = false;
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

	background.Initialize(backgroundTex, "", 0, .7f);
	//	sprite1.Initialize(combined32, 1, .2f);
	//sprite1.Initialize(sprite1Tex, sprite1Mat, 1, .1f);
	//sprite2.Initialize(sprite1Tex, sprite1Mat, 2, .2f);
	//sprite3.Initialize(sprite1Tex, sprite1Mat, 3, .3f);
	playCard.Initialize(playCardTex, playCardMat, 4, .6f);

	temp.initializeImage(.1f);
	sprite1.SetScale({ 0.2f, 0.2f });
	sprite1.SetPosition({ -.5f, -.75f });
	sprite2.SetScale({ 0.2f,0.2f });
	sprite2.SetPosition({ -.15f,-.75f });
	sprite3.SetScale({ 0.2f,0.2f });
	sprite3.SetPosition({.15f, -.75f});
	playCard.SetScale({ 0.2f, 0.2f });
	playCard.SetPosition({ 0.5f, .0f });

	// callbacks
	glfwSetMouseButtonCallback(w, MouseButton);
	glfwSetCursorPosCallback(w, MouseMove);
	glfwSetScrollCallback(w, MouseWheel);
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
			temp.Display();
			glfwSwapBuffers(w);
			glfwPollEvents();

		}
	}
	// terminate
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	background.Release();
	start_button.Release();
	startBackground.Release();
	sprite1.Release();
	sprite2.Release();
	sprite3.Release();
	playCard.Release();
	glfwDestroyWindow(w);
	glfwTerminate();
}
