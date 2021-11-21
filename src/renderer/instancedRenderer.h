#include "../render_data/geometry.h"
#include "../render_data/shader.h"
#include "../render_data/textureAtlas.h"
#include "../game_object/gameObject.h"

#define INSTANCE_COUNT 100

class InstancedRenderer {
public:
    InstancedRenderer();
    ~InstancedRenderer();
    Shader& GetShader() {return shader;}
    //TextureAtlas& Atlas() {return textureAtlas;}

    void Init();
    void Draw(std::vector<GameObject>& gameobjects);


private:
    bool geometrySet = false;

    Shader shader;
    TextureAtlas textureAtlas;
    Geometry geometry;

    unsigned int vao, vbo, ebo;

    //  transformation buffer
    unsigned int instanceMatVbo;
    unsigned int texCoordVbo;

    int matrixCount = 0;
    std::vector<glm::mat4> modelMatrices;
};
