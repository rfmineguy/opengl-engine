#pragma once
#include "../../vendor/stb/stb_image.h"
#include "glad/glad.h"

#define TEXTURE_PATH "res/textures/"

class Texture {
public:
    Texture();
    ~Texture();
    void Load(const char* filepath);
    void Bind(int offset = 0);
    void Unbind();

public:
    int mWidth, mHeight, mChannels;

private:
    unsigned int textureHandle;
    unsigned char* data;
};
