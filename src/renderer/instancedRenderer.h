#include "../render_data/geometry.h"
#include "../render_data/shader.h"
#include "../render_data/textureAtlas.h"

#define INSTANCE_COUNT 100

class InstancedRenderer {
public:
    InstancedRenderer();
    ~InstancedRenderer();
    Shader& GetShader() {return shader;}
    //TextureAtlas& Atlas() {return textureAtlas;}

    void SetGeometry(Geometry geometry);
    void UploadModelMatrix(glm::mat4& matrix);
    void Draw();


private:
    bool geometrySet = false;

    Shader shader;
    //TextureAtlas textureAtlas;
    unsigned int vao, vbo, ebo;

    unsigned int buffer;
    int matrixCount = 0;
    std::vector<glm::mat4> modelMatrices;
};
