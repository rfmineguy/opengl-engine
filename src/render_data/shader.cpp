#include "shader.h"
#include "../util/glUtil.h"
#include <string>

Shader::Shader(std::string tag)
    :tag(tag)
{
    CleanAndChange(tag, true);
}

Shader::~Shader() {
}

//default first = false
void Shader::CleanAndChange(std::string _tag, bool first) {
    //don't recompile the shader if its already the right shader
    if (!first && tag == _tag) {
        std::cout << "Shader is already using " << _tag << std::endl;
        return;
    }

    //delete currently created shader program
    glDeleteProgram(shaderProgramHandle);

    //create new shader program with the new shader source
    vertPath = "res/shader/" + tag + "/vert.glsl";
    fragPath = "res/shader/" + tag + "/frag.glsl";
    Init();
}

void Shader::Init() {
    readFile(vertPath, vertexSource);
    readFile(fragPath, fragmentSource);
    
    int success;
    char infoLog[512];
    const char* source;
  
    //VERTEX SHADER
    source = vertexSource.c_str();

    vertexHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexHandle, 1, &source, NULL);
    glCompileShader(vertexHandle);
    glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexHandle, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "Compiled Vertex Shader : " << vertexHandle << std::endl;
    }

    //FRAGMENT SHADER
    source = fragmentSource.c_str();
    
    fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentHandle, 1, &source, NULL);
    glCompileShader(fragmentHandle);
    glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexHandle, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "Compiled Fragment Shader : " << fragmentHandle << std::endl;
    }
    
    //LINK PROGRAM
    shaderProgramHandle = glCreateProgram();
    glAttachShader(shaderProgramHandle, vertexHandle);
    glAttachShader(shaderProgramHandle, fragmentHandle);
    glLinkProgram(shaderProgramHandle);
    glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramHandle, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "Linked Shader Program : " << shaderProgramHandle << std::endl;
    }
    glDeleteShader(fragmentHandle);
    glDeleteShader(vertexHandle);

    std::cout << "Frag -> " << fragmentHandle << " Vert -> " << vertexHandle << " Program -> " << shaderProgramHandle << std::endl;
}

void Shader::Bind() {
    glUseProgram(shaderProgramHandle);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::Set1f(const char* name, float a) {
   int location = GetLocation(name);
   glUniform1f(location, a);
}

void Shader::Set2f(const char* name, float a, float b) {
    int location = GetLocation(name);
    glUniform2f(location, a, b);
}

void Shader::Set3f(const char* name, float a, float b, float c) {
    int location = GetLocation(name);
    glUniform3f(location, a, b, c);
}

void Shader::Set4f(const char* name, float a, float b, float c, float d) {
    int location = GetLocation(name);
    glUniform4f(location, a, b, c, d);
}

void Shader::Set1i(const char* name, int a) {
    int location = GetLocation(name);
    glUniform1i(location, a);
}

void Shader::Set4fv(const char* name, glm::mat4 mat) {
    int location = GetLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

/*
void Shader::SetVec2Array(const char *name, std::vector<Transform> transforms) {
    int location = GetLocation(name);
    for (int i = 0; i < transforms.size(); i++) {
        Set2f(("offsets[" + std::to_string(i) + "]").c_str(), transforms[i].pos.x, transforms[i].pos.y);
    }
}
*/

int Shader::GetLocation(const char* name) {
    glUseProgram(shaderProgramHandle);
    if (uniformCache.find(name) != uniformCache.end()) {
        return uniformCache.at(name);
    }
    int location = glGetUniformLocation(shaderProgramHandle, name);
    if (location == -1) {
        std::cerr << "Uniform requested [" << name << "] doesn't exist in the shader program \'" << tag << "\'." << std::endl;
        return -1;
    }
    uniformCache.emplace(name, location);
    return uniformCache.at(name); 
}
