#pragma once

#include <iostream>
#include <filesystem>

#include "../../vendor/stb/stb_image.h"
#include "glad/glad.h"

namespace Firefly {
class Texture {
public:
    Texture() = default;
    Texture(const std::string& tag, const std::string& path);

    //delete copy ctor
    Texture(const Texture&) = delete;
    //delete copy assignment operator
    Texture& operator=(Texture&) = delete;

    //move ctor
    Texture(Texture&& other);
    //move assignment operator
    Texture& operator=(Texture&& other);

    ~Texture();
    int CleanAndChange(const std::string& tag, bool isAtlas);
    int CleanAndChange(const std::string& path);
    int Load(const char* filepath);
    void Bind(int offset = 0);
    void Unbind();

public:
    int mWidth, mHeight, mChannels;
    unsigned int textureHandle;
    bool isLoaded = false;

    std::string tag;
    std::filesystem::path path;
private:
    unsigned char* data;
};
}
