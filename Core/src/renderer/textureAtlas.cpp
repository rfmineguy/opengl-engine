#include "textureAtlas.h"
#include "../util/stringUtil.h"
#include "region.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <type_traits>
#include "../util/log.h"


namespace Firefly {
TextureAtlas::TextureAtlas(const std::string& tag, const std::string& path) : Texture(),
atlasName(tag){
    this->tag = tag;
    this->path = path;
    LOG_DEBUG("TextureAtlas {} - {}", this->tag.c_str(), this->path.c_str());
    ParseAtlas();
}

TextureAtlas::~TextureAtlas() {
    LOG_WARN("Deleting textureAtlas [{0}]", atlasName);
}

TextureAtlas::TextureAtlas(TextureAtlas&& other) {
    //assign other to this
    LOG_WARN("Moved textureAtlas {0}", other.atlasName);
    atlasName = std::move(other.atlasName);
    srcImageName = std::move(other.srcImageName);
    map = std::move(other.map);
    subTexWidth = other.subTexWidth;
    subTexHeight = other.subTexHeight;
    cellsWide = other.cellsWide;
    cellsTall = other.cellsTall;
    path = std::move(other.path);

    //deinitialize other
    other.atlasName = "";
    other.srcImageName = "";
    other.subTexWidth = 0;
    other.subTexHeight = 0;
    other.cellsWide = 0;
    other.cellsTall = 0;
    other.path = "";
}

TextureAtlas& TextureAtlas::operator = (TextureAtlas&& other) {
    LOG_WARN("Assigned TextureAtlas {0}", other.atlasName);
    atlasName = std::move(other.atlasName);
    srcImageName = std::move(other.srcImageName);
    map = std::move(other.map);
    subTexWidth = other.subTexWidth;
    subTexHeight = other.subTexHeight;
    cellsWide = other.cellsWide;
    cellsTall = other.cellsTall;
    path = std::move(other.path);

    //deinitialize other
    other.atlasName = nullptr;
    other.srcImageName = nullptr;
    other.subTexWidth = 0;
    other.subTexHeight = 0;
    other.cellsWide = 0;
    other.cellsTall = 0;
    other.path = "";

    return *this;
}

/*
 * File format
 *   - line 1 -> [cellwidth cellheight imagename]
 *   - rest   -> [name xcell ycell]
 */
void TextureAtlas::ParseAtlas() {
    LOG_INFO("ParseAtlas started");
   
    cellsWide = 4;
    cellsTall = 4;

    int currentLine = 0;
    std::ifstream ifs(this->path);
    if (ifs.fail()) {
        LOG_ERROR("Failed to open file {0}", this->path);
    }
    else {
        std::string s;

        //line 0 -> describes the file
        getline(ifs, s);
        eraseCharacters(s, "[]");
        std::vector<std::string> tokens = splitBy(s, ' ');
        LOG_INFO("{}", tokens.size());
        for (std::string s : tokens) {
            LOG_INFO("{}", s);
        }

        subTexWidth = std::stoi(tokens[0]);
        subTexHeight = std::stoi(tokens[1]);
        LOG_INFO("{} {}", subTexWidth, subTexHeight);
        srcImageName = tokens[2];
        //std::cout << "tokens[2] - " << srcImageName << std::endl;
        /**
         *  atlasPath = "testAtlas"
         *  srcImageName = "texture.png"
         *  sent -> "testAtlas/texture.png"
         */
        int loadStatus = CleanAndChange(srcImageName, true);
        if (loadStatus != 0) {
            LOG_ERROR("Failed to load texture {0}", srcImageName);
        }
        else {
            LOG_INFO("Loaded texture {0}", srcImageName);
        }
        cellsWide = mWidth / subTexWidth;
        cellsTall = mHeight / subTexHeight;
    
        //rest of the file
        while (getline(ifs, s)) {
            if (s.empty()) continue;
            eraseCharacters(s, "[]");
            tokens = splitBy(s, ' ');//[0]->name  [1]->x  [2]->y
            
            /*for (int i = 0; i < tokens.size(); i++) {
                std::cout << tokens[i] << std::endl;
            }*/

            Region region = SubRegion(charToInt(tokens[1][0]), charToInt(tokens[2][0]));
            map.emplace(
                    tokens[0],
                    region
                );
        }
    }
    LOG_INFO("Finished ParseAtlas\n");
}
/*
 * col = 1
 * row = 0
 *
 * tl_x = (1.0 / cellsWide) * col
 * tl_y = 1 - ((1.0 / cellsTall) * row)
 * br_x = tl_x + (1.0 / cellsWide)
 * br_y = tl_y - (1.0 / cellsTall)
 *
 * TODO: the problem is here
 */
Region TextureAtlas::SubRegion(int col, int row) {
    float topLeftX = (1.0 / cellsWide) * col; //  top left texture coordinate
    float topLeftY = 1 - ((1.0 / cellsTall) * row); //
    float bottomRightX = topLeftX + (1.0 / cellsWide);
    float bottomRightY = topLeftY - (1.0 / cellsTall);

    return { 
        glm::vec2(bottomRightX, topLeftY),      //top-right
        glm::vec2(topLeftX, topLeftY),          //top-left
        glm::vec2(bottomRightX, bottomRightY),  //bottom-right
        glm::vec2(topLeftX, bottomRightY),       //bottom-left
    };
}

Region TextureAtlas::GetRegion(std::string name) {
    if (map.find(name) == map.end()) {
        LOG_ERROR("{0} is an invalid region", name);
        return {};
    }
    return map.at(name);
}

void TextureAtlas::Print() {
    for (auto pair : map) {
        LOG_INFO("\t {} \t\t- [{:03.2f} {:03.2f}] [{:03.2f} {:03.2f}]",
                pair.first.c_str(), 
                pair.second.topleft.x, pair.second.topleft.y,
                pair.second.bottomright.x, pair.second.bottomright.y);
    }
}
}
