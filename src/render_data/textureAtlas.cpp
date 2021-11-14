#include "textureAtlas.h"
#include "../util/stringUtil.h"
#include "region.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <type_traits>

TextureAtlas::TextureAtlas(std::string atlasPath)
:atlasPath(atlasPath){
    ParseAtlas(); 
}

TextureAtlas::~TextureAtlas() {
}

/*
 * File format
 *   - line 1 -> [cellwidth cellheight imagename]
 *   - rest   -> [name xcell ycell]
 */
void TextureAtlas::ParseAtlas() {
    std::cout << std::endl << std::endl << "start ParseAtlas()" << std::endl;
    int currentLine = 0;
    std::ifstream ifs("res/textures/" + atlasPath + "/testing.atlas");
    if (ifs.fail()) {
        std::cerr << "Failed to open file : " << atlasPath << std::endl;
    }
    else {
        std::string s;

        //line 0 -> describes the file
        getline(ifs, s);
        eraseCharacters(s, "[]");
        std::vector<std::string> tokens = splitBy(s, ' ');

        subTexWidth = std::stoi(tokens[0]);
        subTexHeight = std::stoi(tokens[1]);
        srcImageName = tokens[2];
        //std::cout << "tokens[2] - " << srcImageName << std::endl;
        Load((atlasPath + "/" + srcImageName).c_str());
        std::cout << "Fully loaded texture successfully" << std::endl;

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
            std::cout << tokens[0] << " : " << region.ToString() << std::endl;
            map.emplace(
                    tokens[0],
                    region
                );
            std::cout << "Inserted successfully" << std::endl;
        }
    }
    std::cout << "end ParseAtlas()" << std::endl;
}
/*
 * col = 1
 * row = 0
 *
 * tl_x = (1.0 / cellsWide) * col
 * tl_y = 1 - ((1.0 / cellsTall) * row)
 * br_x = tl_x + (1.0 / cellsWide)
 * br_y = tl_y - (1.0 / cellsTall)
 */
Region TextureAtlas::SubRegion(int col, int row) {
    std::cout << "Col : " << col << "  Row : " << row << std::endl;
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
        std::cerr << "Not a valid region" << std::endl;
    }
    return map.at(name);
}

void TextureAtlas::Print() {
    for (auto pair : map) {
        printf("%s :: {%0.4f %0.4f} {%0.4f %0.4f}\n",
                pair.first.c_str(),
                pair.second.topleft.x, pair.second.topleft.y,
                pair.second.bottomright.x, pair.second.bottomright.y);
    }
}
