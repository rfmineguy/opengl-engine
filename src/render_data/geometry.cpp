#include "geometry.h"
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

Geometry::Geometry() {}

Geometry::~Geometry() {
    mVertices.clear();
    delete mVertices.data();
}

void Geometry::AddVertex(Vertex v) {
    mVertices.push_back(v);
    size_t bytes = sizeof(mVertices[0]) * mVertices.size(); 
    std::cout << "Size : " << mVertices.size() << "  " << bytes << std::endl;
}

void Geometry::SetElements(std::vector<unsigned int> indices) {
    mIndices = indices;
}

void Geometry::Bake() {
    
}

Vertex& Geometry::GetVertex(int index) {
    return mVertices.at(index);
}

void Geometry::Print() {
    for (int i = 0; i < mVertices.size(); i++) {
        Vertex v = mVertices.at(i);
        printf("{x=%0.4f y=%0.4f z=%0.4f} {texX=%0.4f texY=%0.4f}\n"
                , v.pos.x, v.pos.y, v.pos.z
                , v.texCoord.x, v.texCoord.y);
    }
    for (int i = 0; i < mIndices.size(); i+=6) { 
        printf("[%d %d %d %d %d %d]\n", mIndices[i], mIndices[i+1], mIndices[i+2], mIndices[i+3], mIndices[i+4], mIndices[i+5]);
    }
}

Geometry& Geometry::SetPosition(int x, int y) {
    model = glm::translate(model, glm::vec3(0));
    model = glm::translate(model, glm::vec3(x, y, 0));
    return *this;
}

Geometry& Geometry::Rotate(float rotation) {
    model = glm::rotate(model, 0.f, glm::vec3(0, 0, 1));
    model = glm::rotate(model, rotation, glm::vec3(0, 0, 1));
    return *this;
}

Geometry& Geometry::Translate(int dx, int dy, int dz) {
    model = glm::translate(model, glm::vec3(0, 0, 0));
    model = glm::translate(model, glm::vec3(dx, dy, dz));
    return *this;
}


Geometry& Geometry::Size(float width, float height) {
    if (type == QUAD) {
        //[0] -> top-right
        //[1] -> bottom-right
        //[2] -> bottom-left
        //[3] -> top-left

        float xsize = mVertices[3].pos.x + width;
        float ysize = mVertices[3].pos.y + height;

        mVertices[0].pos.x = xsize;
        mVertices[1].pos.x = xsize;
        mVertices[1].pos.y = ysize;
        mVertices[2].pos.y = ysize;

        size.x = mVertices[1].pos.x - mVertices[3].pos.x; //br.x - tl.x
        size.y = mVertices[1].pos.y - mVertices[3].pos.y; //br.y - tl.y
    }
    return *this;
}
