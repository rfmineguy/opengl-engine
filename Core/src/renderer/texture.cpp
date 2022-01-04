#include "texture.h"
#include <iostream>
#include "../util/log.h"

namespace Firefly {
Texture::Texture(const std::string& tag, const std::string& path)
{
    this->path = path;
    //CleanAndChange(tag, false);
    Load(path.c_str());
    this->tag = tag;
}

Texture::Texture(Texture&& other) {
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mChannels = other.mChannels;
    textureHandle = other.textureHandle;
    isLoaded = other.isLoaded;
    tag = other.tag;
    path = other.path;
    data = other.data;

    other.mWidth = 0;
    other.mHeight = 0;
    other.mChannels = 0;
    other.textureHandle = 0; //not sure. but i think this is right
    other.isLoaded = false;
    other.tag = "";
    other.path = "";
    other.data = nullptr;
    CleanAndChange(tag, false);
}

Texture& Texture::operator=(Texture&& other) {
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mChannels = other.mChannels;
    textureHandle = other.textureHandle;
    isLoaded = other.isLoaded;
    tag = other.tag;
    path = other.path;
    data = other.data;

    other.mWidth = 0;
    other.mHeight = 0;
    other.mChannels = 0;
    other.textureHandle = 0; //not sure. but i think this is right
    other.isLoaded = false;
    other.tag = "";
    other.path = "";
    other.data = nullptr;
    CleanAndChange(tag, false);
    return *this;
}

Texture::~Texture() {
    LOG_WARN("Deleted texture [{0}]", path.string().c_str());
    Unbind();
    glDeleteTextures(1, &textureHandle);
    data = nullptr;
}

//  atlas = true
//    tag -> folder name + "/" + image name<.png>
//  atlas = false
//    tag -> image name<.png>
/*
 * error loading texture  @return -1
 * no errors              @return 0
 * texture already in use @return 1
 */

int Texture::CleanAndChange(const std::string& _tag, bool isAtlas) {
    if (tag == _tag) {
        LOG_WARN("Texture already assigned to {0}", _tag);
        return 1;
    }
    if (isAtlas) {
        path = "res/atlases/" + _tag;
    } 
    else {
        path = "res/textures/" + _tag;
    }
    glDeleteTextures(1, &textureHandle);
    return Load(path.c_str());
}

int Texture::CleanAndChange(const std::string& _path) {
    path = _path;
    glDeleteTextures(1, &textureHandle);
    return Load(path.c_str());
}

//filepath should be relative to 'res/textures/'
int Texture::Load(const char* filepath) {
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    std::string fullPath = std::string(filepath);
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
        LOG_INFO("Loaded image [{0} x {1} - channels [{2}]]", mWidth, mHeight, mChannels);
    }
    else {
        LOG_CRITICAL("Failed to load texture '{0}'", fullPath);
        return -1;
    }
    stbi_image_free(data);
    isLoaded = true;
    return 0;
}

void Texture::Bind(int offset) {
    glActiveTexture(GL_TEXTURE0 + offset);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
}
