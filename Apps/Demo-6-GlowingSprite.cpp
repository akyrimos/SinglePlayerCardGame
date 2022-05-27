// GlowingSprite.cpp

#include <glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "GlowSprite.h"

Sprite background;
GlowSprite actor;
time_t start = clock();

void Glow() {
	float glowDuration = 4, pause = 2; // in seconds
	float amplitude = 2;
	float dt = (float)(clock()-start)/CLOCKS_PER_SEC;
	if (dt > pause) {
		float t = .75f+(dt-pause)/glowDuration, angle = 2*3.141592f*t;
		actor.glow = amplitude*(1+sin(angle))/2;
	}
}

void Display() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background.Display();
	actor.Display();
	glFlush();
}

void Resize(GLFWwindow *w, int width, int height) { glViewport(0, 0, width, height); }

int main() {
	// init app window, GL context, callbacks
	glfwInit();
	GLFWwindow *w = glfwCreateWindow(600, 600, "Glowing Sprite", NULL, NULL);
	glfwSetWindowPos(w, 100, 100);
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSetWindowSizeCallback(w, Resize);
	// read background, actor sprites
	string dir = "../Lib/Images/";
	string bg = dir + "fightbackground.png";
	string player = dir + "defend.png";
	background.Initialize(bg);
	actor.Initialize(player);
	// event loop
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(w)) {
		Glow();
		Display();
		glfwSwapBuffers(w);
		glfwPollEvents();
	}
	// terminate
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwDestroyWindow(w);
	glfwTerminate();
}
