#include <glad/glad.h>
#include <fstream>
#include <ios>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>

//
//  File functions
//
inline void readFile(std::string path, std::string& contents) {
    std::ifstream ifs;
    ifs.open(path, std::ios::in);
    if (ifs.fail()) {
        std::cerr << std::strerror(errno) << std::endl;
    }
    if (ifs.is_open()) {
        std::string s;
        std::stringstream ss;
        while(std::getline(ifs, s)) {
            ss << s << "\n";
        }
        contents = ss.str();
        ifs.close();
    }
}

//
//  Vertex Array functions
//
inline void setupBuffers(unsigned int vao, unsigned int vbo, unsigned int ebo) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
}

inline void setData(unsigned int vbo, unsigned int ebo, float* vertices, unsigned int* indices) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
