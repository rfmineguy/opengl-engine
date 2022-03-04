#include "core/corepch.h"
#include "renderer/vertex.h"

namespace Firefly {
class Quad {
public:
    Quad();
    ~Quad();
    void Bind();
    void Unbind();
    int VBO_Size() { return vertices.size(); }
    int EBO_Size() { return indices.size(); }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:
    unsigned int vao, vbo, ebo;
    unsigned int texVbo;
};
}
