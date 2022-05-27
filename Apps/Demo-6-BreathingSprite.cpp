// BreathingSprite.cpp

#include <glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "Sprite.h"

Sprite background, actor;
time_t start = clock();

void Breathe() {
	float breathDuration = 2; // in seconds
	float bias = 1, amplitude = .5f;
	float dt = (float)(clock()-start)/CLOCKS_PER_SEC;
	float angle = 2*3.141592f*dt/breathDuration;
	float vscale = bias+amplitude*(1+sin(angle))/2;
	actor.SetScale(vec2(.7f, .7f*vscale));
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
	GLFWwindow *w = glfwCreateWindow(600, 600, "Breathing Sprite", NULL, NULL);
	glfwSetWindowPos(w, 100, 100);
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSetWindowSizeCallback(w, Resize);
	// read background, actor sprites
	string dir = "../Lib/Images/";
	string bg = dir + "fightbackground.png";
	string player = dir + "Player.png";
	background.Initialize(bg);
	actor.Initialize(player);
	// event loop
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(w)) {
		Breathe();
		Display();
		glfwSwapBuffers(w);
		glfwPollEvents();
	}
	// terminate
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwDestroyWindow(w);
	glfwTerminate();
}
