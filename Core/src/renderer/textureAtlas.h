#pragma once
#include "texture.h"
#include "region.h"
#include <map>

namespace Firefly {
class TextureAtlas : public Texture {
public:
    TextureAtlas() = default;
    TextureAtlas(const std::string& tag, const std::string& path);
    
    //delete copy ctor
    TextureAtlas(const TextureAtlas&) = delete;
    //delete copy assignment operator
    TextureAtlas& operator=(TextureAtlas&) = delete;

    //move ctor
    TextureAtlas(TextureAtlas&& other);
    //move assignment operator
    TextureAtlas& operator=(TextureAtlas&& other);

    ~TextureAtlas();
    Region SubRegion(int col, int row);
    Region GetRegion(std::string name);
    void Print();

private:
    void ParseAtlas();

public:
    std::string atlasName;

private:
    std::string srcImageName;
    std::map<std::string, Region> map;

    int subTexWidth, subTexHeight;
    int cellsWide, cellsTall;         //how many cells across and top to bottom

friend class ImGuiPropertiesPanel;
};
}
