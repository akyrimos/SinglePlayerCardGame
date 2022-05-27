// GlowSprite.cpp

#include "GLXtras.h"
#include "GlowSprite.h"

GLuint glowSpriteShader = 0;

namespace Glow {
	void BuildShader() {
		const char *vShader = R"(
			#version 330
			uniform mat4 view;
			uniform float z = 0;
			out vec2 uv;
			void main() {
				vec2 pts[] = vec2[4](vec2(-1,-1), vec2(-1,1), vec2(1,1), vec2(1,-1));
				uv = (vec2(1,1)+pts[gl_VertexID])/2;
				gl_Position = view*vec4(pts[gl_VertexID], z, 1);
			}
		)";
		const char *pShader = R"(
			#version 330
			in vec2 uv;
			out vec4 pColor;
			uniform float glow = 0;
			uniform mat4 uvTransform;
			uniform sampler2D textureImage;
			uniform sampler2D textureMat;
			uniform bool useMat;
			uniform int nTexChannels = 3;
			void main() {
				vec2 st = (uvTransform*vec4(uv, 0, 1)).xy;
				if (nTexChannels == 4)
					pColor = texture(textureImage, st);
				else {
					pColor.rgb = texture(textureImage, st).rgb;
					pColor.a = useMat? texture(textureMat, st).r : 1;
				}
				if (pColor.a < .02) // if nearly full matte,
					discard;		// don't tag z-buffer
				pColor.rgb *= (1+glow);
			}
		)";
		glowSpriteShader = LinkProgramViaCode(&vShader, &pShader);
	}
} // end namespace

void GlowSprite::Display(mat4 *fullview, int textureUnit) {
	if (!glowSpriteShader)
		Glow::BuildShader();
	glUseProgram(glowSpriteShader);
	glActiveTexture(GL_TEXTURE0+textureUnit);
	if (nFrames) { // animation
		time_t now = clock();
		if (now > change) {
			frame = (frame+1)%nFrames;
			change = now+(time_t)(frameDuration*CLOCKS_PER_SEC);
		}
		glBindTexture(GL_TEXTURE_2D, textureNames[frame]);
	}
	else glBindTexture(GL_TEXTURE_2D, textureName);
	SetUniform(glowSpriteShader, "textureImage", (int) textureUnit);
	SetUniform(glowSpriteShader, "useMat", matName > 0);
	SetUniform(glowSpriteShader, "nTexChannels", nTexChannels);
	SetUniform(glowSpriteShader, "z", z);
	SetUniform(glowSpriteShader, "glow", glow);
	if (matName > 0) {
		glActiveTexture(GL_TEXTURE0+textureUnit+1);
		glBindTexture(GL_TEXTURE_2D, matName);
		SetUniform(glowSpriteShader, "textureMat", (int) textureUnit+1);
	}
	SetUniform(glowSpriteShader, "view", fullview? *fullview*ptTransform : ptTransform);
	SetUniform(glowSpriteShader, "uvTransform", uvTransform);
	glDrawArrays(GL_QUADS, 0, 4);
}
