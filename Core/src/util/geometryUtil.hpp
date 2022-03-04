#include "renderer/geometry.h"
#include "renderer/region.h"

using namespace glm;

inline Geometry& initQuad(Geometry& geometry) {

    //Vertex layout
    //  position
    //  color
    //  texCoord
    // vec2 topLeftTex = region.topleft;
    // vec2 topRightTex = region.topright;
    // vec2 bottomLeftTex = region.bottomleft;
    // vec2 bottomRightTex = region.bottomright;

    //defaults
    //size 1x1
    //color white
    geometry.AddVertex({ vec3 ( 1.0f,  1.0f, 0.0f ), vec2(1.0f, 1.0f) });  //top right
    geometry.AddVertex({ vec3 ( 1.0f,  0.0f, 0.0f ), vec2(1.0f, 0.0f) });  //bottom right
    geometry.AddVertex({ vec3 ( 0.0f,  0.0f, 0.0f ), vec2(0.0f, 0.0f) });  //bottom left
    geometry.AddVertex({ vec3 ( 0.0f,  1.0f, 0.0f ), vec2(0.0f, 1.0f) });  //top left

    //indices should be 24 bytes
    geometry.SetElements({0, 1, 3, 1, 2, 3});
    geometry.type = GeometryType::QUAD;
    return geometry;
}
