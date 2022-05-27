// StepbackSprite.cpp

#include <glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "Sprite.h"

int winWidth = 600, winHeight = 600;
Sprite background, actor;

// step back
bool released = false;
time_t releaseTime = 0;
vec2 startLoc, releaseLoc;

void Stepback() {
	if (!released) return;
	float stepPause = 1.5f, stepDuration = 1; // in seconds
	float dtRelease = (float)(clock()-releaseTime)/CLOCKS_PER_SEC;
	if (dtRelease < stepPause) return;
	float dtStep = dtRelease-stepPause;
	if (dtStep > stepDuration) return;
	float t = dtStep/stepDuration;
	vec2 newLoc = releaseLoc+t*(startLoc-releaseLoc);
	actor.SetPosition(newLoc);
}

void Display() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background.Display();
	actor.Display();
	glFlush();
}

void MouseButton(GLFWwindow *w, int butn, int action, int mods) {
	double x, y;
	glfwGetCursorPos(w, &x, &y);
	y = winHeight-y;
	if (action == GLFW_PRESS) {
		startLoc = actor.GetPosition();
		actor.MouseDown(vec2((float) x, (float) y));
	}
	if (action == GLFW_RELEASE) {
		released = true;
		releaseTime = clock();
		releaseLoc = actor.GetPosition();
	}
}

void MouseMove(GLFWwindow *w, double x, double y) {
	y = winHeight-y;
	if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		actor.MouseDrag(vec2((float) x, (float) y));
}

void Resize(GLFWwindow *w, int width, int height) {
	glViewport(0, 0, winWidth = width, winHeight = height);
}

int main() {
	// init app window, GL context, callbacks
	glfwInit();
	GLFWwindow *w = glfwCreateWindow(winWidth, winHeight, "Sprite Stepback", NULL, NULL);
	glfwSetWindowPos(w, 100, 100);
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSetMouseButtonCallback(w, MouseButton);
	glfwSetCursorPosCallback(w, MouseMove);
	glfwSetWindowSizeCallback(w, Resize);
	// read background, foreground sprites
	string dir = "../Lib/Images/";
	string bg = dir + "fightbackground.png";
	string sprite = dir + "alien_slime.png";
	background.Initialize(bg);
	actor.Initialize(sprite);
	actor.SetScale(vec2(.5f, .5f));
	// event loop
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(w)) {
		Stepback();
		Display();
		glfwSwapBuffers(w);
		glfwPollEvents();
	}
	// terminate
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwDestroyWindow(w);
	glfwTerminate();
}
