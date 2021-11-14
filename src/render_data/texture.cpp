#include "texture.h"
#include <iostream>

Texture::Texture() {

}

Texture::~Texture() {
    Unbind();
    glDeleteTextures(1, &textureHandle);
}

//filepath should be relative to 'res/textures/'
void Texture::Load(const char* filepath) {

    std::cout << "Loading " << filepath << std::endl;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    std::string fullPath = TEXTURE_PATH + std::string(filepath);
    data = stbi_load(fullPath.c_str(), &mWidth, &mHeight, &mChannels, 0);
    if (data) {
        if (mChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (mChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Loaded [" << mWidth << "x" << mHeight << " - channels [" << mChannels << "] ] image - " << std::endl;
    }
    else {
        std::cerr << "Failed to load texture '" << filepath << "'" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::Bind(int offset) {
    glActiveTexture(GL_TEXTURE0 + offset);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
