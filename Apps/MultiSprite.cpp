// MultiSprite.cpp - multiple movable, selectable, layered sprites

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "GLXtras.h"
#include "Misc.h"
#include "Sprite.h"

int winWidth = 600, winHeight = 600;
Sprite background, sprite1, sprite2, sprite3, playCard, *selected = NULL;
string dir = "../Lib/Images/";
string sprite1Tex = dir+"attack card.png", sprite1Mat = dir+"attack card.png";
string playCardTex = dir + "playcard.png", playCardMat = dir + "playcard.png";
string combined32 = dir+"Combined32.png"; // png, tga ok; bmp, jpg do not support 32
string backgroundTex = dir+"Outline.png";



// Display

void Display() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	background.Display();
	sprite1.Display();
	sprite2.Display();
	sprite3.Display();
	playCard.Display();
	glFlush();
}

// Mouse

void MouseButton(GLFWwindow *w, int butn, int action, int mods) {
	double x, y;
	glfwGetCursorPos(w, &x, &y);
	y = winHeight-y; // invert y for upward-increasing screen space
	if (action == GLFW_PRESS) {
		int ix = (int) x, iy = (int) y;
		selected = NULL;
		if (sprite1.Hit(ix, iy)) selected = &sprite1;
		if (sprite2.Hit(ix, iy)) selected = &sprite2;
		if (sprite3.Hit(ix, iy)) selected = &sprite3;
		if (selected)
			selected->MouseDown(vec2((float) x, (float) y));
	}

	if (action == GLFW_RELEASE) {
		if (selected) {
			if (selected->Intersect(playCard))
				selected->SetPosition({ -5.0f, -5.0f });
		}
		selected = NULL;
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
	GLFWwindow* w = glfwCreateWindow(winWidth, winHeight, "MultiSprite", NULL, NULL);
	glfwSetWindowPos(w, 100, 100);
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// read background, foreground, and mat textures
	background.Initialize(backgroundTex, "", 0, .7f);
	//	sprite1.Initialize(combined32, 1, .2f);
	sprite1.Initialize(sprite1Tex, sprite1Mat, 1, .1f);
	sprite2.Initialize(sprite1Tex, sprite1Mat, 2, .2f);
	sprite3.Initialize(sprite1Tex, sprite1Mat, 3, .3f);
	playCard.Initialize(playCardTex, playCardMat, 4, .6f);
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
		Display();
		glfwSwapBuffers(w);
		glfwPollEvents();
	}
	// terminate
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	background.Release();
	sprite1.Release();
	sprite2.Release();
	sprite3.Release();
	playCard.Release();
	glfwDestroyWindow(w);
	glfwTerminate();
}
