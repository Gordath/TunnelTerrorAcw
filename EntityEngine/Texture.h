#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "Resource.h"

enum TextureType {
	TEX_DIFFUSE,
	TEX_SPECULAR,
	TEX_NORMAL,
	NUM_TEXTURES
};

class Texture : public Resource {
};

#endif //TEXTURE_H_
