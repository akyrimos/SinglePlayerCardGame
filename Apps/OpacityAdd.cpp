// OpacityAdd.cpp - add opacity layer to 24 bit image
// console only requests directory, image, and matte

#include <stdio.h>
#include <string.h>
#include "Misc.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#define DISPLAY_APP
#ifdef DISPLAY_APP
	#include <glad.h>                                         
	#include <glfw3.h>                                        
	#include "GLXtras.h"
	GLuint program = 0;
	GLuint textureName = 0, textureUnit = 0;
	const char *vertexShader = R"(
		#version 130
		out vec2 vuv;
		void main() {
			vec2 pt[] = vec2[4](vec2(-1,-1), vec2(-1,1), vec2(1,1), vec2(1,-1));
			vec2 uv[] = vec2[4](vec2(0,0), vec2(0,1), vec2(1,1), vec2(1,0));
			vuv = uv[gl_VertexID];
			gl_Position = vec4(pt[gl_VertexID], 0, 1);
		}
	)";
	const char *pixelShader = R"(
		#version 130
		in vec2 vuv;                                                    // from vertex shader
		uniform sampler2D textureImage;                                 // from CPU
		out vec4 pColor;
		void main() {
			pColor = texture(textureImage, vuv);
			if (pColor.a < .02) // if nearly transparent,
				discard;		// don't tag z-buffer
		}
	)";
#endif

using std::string;

bool Write32(const char *image, const char *matte, const char *out) {
	const char *ext = strlen(out) > 3? out+strlen(out)-3 : NULL;
	int width, height;
	unsigned char *oData = MergeFiles(image, matte, width, height);
	int r = !strcmp(ext, "png")? stbi_write_png(out, width, height, 4, oData, width*4) :
			!strcmp(ext, "tga")? stbi_write_tga(out, width, height, 4, oData) :
			0; // bmp, jpg do not (?) support 4 channels
	delete [] oData;
	printf("%s %s\n", out, r? "written" : "write failure");
	return r != 0;
}

void GetInput(const char *prompt, char *buf) {
	printf("%s: ", prompt);
	fgets(buf, 500, stdin);
	if (strlen(buf) > 1) buf[strlen(buf)-1] = 0; // remove <cr>
}

#ifdef DISPLAY_APP
	void Display() {
		glClearColor(0, 0, 0, 1);                                       // set background color
		glClear(GL_COLOR_BUFFER_BIT);                                   // clear background
		glUseProgram(program);
		glActiveTexture(GL_TEXTURE0+textureUnit);                       // make texture active
		glBindTexture(GL_TEXTURE_2D, textureName);
		SetUniform(program, "textureImage", (int) textureUnit);         // set texture map for pixel shader
		glDrawArrays(GL_QUADS, 0, 4);                                   // draw object                     
		glFlush();                                                      // finish scene
	}
	int main() {
		glfwInit();
		GLFWwindow *w = glfwCreateWindow(600, 600, "Opacity Add", NULL, NULL);
		glfwSetWindowPos(w, 200, 200);
		glfwMakeContextCurrent(w);
		gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		program = LinkProgramViaCode(&vertexShader, &pixelShader);
		char directory[500], image[500], matte[500], out[500];
		while (!glfwWindowShouldClose(w)) {
			GetInput("directory", directory);
			if (directory[strlen(directory)-1] == '/')
				directory[strlen(directory)-1] = 0;
			GetInput("picture (any type)", image);
			GetInput("matte (any type)", matte);
			GetInput("output (png or tga only)", out);
			string dir(directory), dImage = dir+"/"+image, dMatte = dir+"/"+matte, dOut = dir+"/"+out;
			bool ok = Write32(dImage.c_str(), dMatte.c_str(), dOut.c_str());
			textureName = LoadTexture(dOut.c_str());
			Display();
			glfwSwapBuffers(w);                          
			glfwPollEvents();
		}
		glfwDestroyWindow(w);
		glfwTerminate();
	}
#else
int main(int ac, char **av) {
	char directory[500], picture[500], matte[500], out32[500];
	GetInput("directory", directory);
	printf("\n");
	while (true) {
		GetInput("picture (any type)", picture);
		GetInput("matte (any type)", matte);
		GetInput("output (png or tga only)", out32);
		bool ok = Write32(directory, picture, matte, out32);
		printf("%s %s\n\n", out32, ok? "written" : "write failed");
	}
}
#endif
