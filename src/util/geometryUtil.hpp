#include "../render_data/geometry.h"
#include "../render_data/region.h"

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

inline Geometry& initCube(Geometry& geometry, Region region) {
    //Vertex layout
    //  position
    //  color
    //  texCoord
    vec2 topLeftTex = region.topleft;
    vec2 topRightTex = vec2(region.bottomright.x, region.topleft.y);
    vec2 bottomLeftTex = vec2(region.topleft.x, region.bottomright.y);
    vec2 bottomRightTex = region.bottomright;
    
    geometry.AddVertex({ vec3 (-1.0f, -1.0f, 0.5f), topLeftTex});
    geometry.AddVertex({ vec3 ( 1.0f, -1.0f, 0.5f), bottomRightTex});
    geometry.AddVertex({ vec3 (-1.0f,  1.0f, 0.5f), topLeftTex});
    geometry.AddVertex({ vec3 ( 1.0f,  1.0f, 0.5f), bottomRightTex});

    geometry.AddVertex({ vec3 (-1.0f, -1.0f, -0.5f), topLeftTex});
    geometry.AddVertex({ vec3 ( 1.0f, -1.0f, -0.5f), bottomRightTex});
    geometry.AddVertex({ vec3 (-1.0f,  1.0f, -0.5f), topLeftTex});
    geometry.AddVertex({ vec3 ( 1.0f,  1.0f, -0.5f), bottomRightTex});
    
    geometry.SetElements({        
        //Top
        2, 6, 7,
        2, 3, 7,
        //Bottom
        0, 4, 5,
        0, 1, 5,
        //Left
        0, 2, 6,
        0, 4, 6,
        //Right
        1, 3, 7,
        1, 5, 7,
        //Front
        0, 2, 3,
        0, 1, 3,
        //Back
        4, 6, 7,
        4, 5, 7});
    geometry.type = GeometryType::CUBE;
    return geometry;
}
