// GlowSprite.h

#ifndef GLOW_SPRITE_HDR
#define GLOW_SPRITE_HDR

#include "Sprite.h"

class GlowSprite: public Sprite {
public:
	float glow = 0;
	void Display(mat4 *view = NULL, int textureUnit = 0);
};

#endif
