#pragma once
#include "texture.h"
#include "region.h"
#include <string>
#include <map>

class TextureAtlas : public Texture {
public:
    TextureAtlas(std::string atlasPath);
    ~TextureAtlas();
    Region SubRegion(int col, int row);
    Region GetRegion(std::string name);
    void Print();

private:
    void ParseAtlas();

private:
    std::string atlasPath;
    std::string srcImageName;
    std::map<std::string, Region> map;

    int subTexWidth, subTexHeight;
    int cellsWide, cellsTall;         //how many cells across and top to bottom
};
