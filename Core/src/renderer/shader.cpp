#include <string>

#include "shader.h"
#include "../util/fileUtil.h"
#include "../util/log.h"

namespace Firefly {
Shader::Shader(const std::string& tag, const std::string& path)
    :tag(tag)
{
    this->tag = tag;
    this->path = path;
    CleanAndChange(tag, true);
}

Shader::Shader(Shader&& other)
{
    tag = std::move(other.tag);
    vertPath = std::move(other.vertPath);
    fragPath = std::move(other.fragPath);
    vertexSource = std::move(other.vertexSource);
    fragmentSource = std::move(other.fragmentSource);
    fragmentHandle = other.fragmentHandle;
    vertexHandle = other.vertexHandle;
    shaderProgramHandle = other.shaderProgramHandle;
    uniformCache = std::move(other.uniformCache);

    other.tag = "";
    other.vertPath = "";
    other.fragPath = "";
    other.vertexSource = "";
    other.fragmentSource = "";
    other.fragmentHandle = -1;
    other.vertexHandle = -1;
    other.shaderProgramHandle = -1;
    other.uniformCache.clear();
    LOG_INFO("Moved shader [{}]", tag);
}

Shader& Shader::operator=(Shader&& other) {
    tag = std::move(other.tag);
    vertPath = std::move(other.vertPath);
    fragPath = std::move(other.fragPath);
    vertexSource = std::move(other.vertexSource);
    fragmentSource = std::move(other.fragmentSource);
    fragmentHandle = other.fragmentHandle;
    vertexHandle = other.vertexHandle;
    shaderProgramHandle = other.shaderProgramHandle;
    uniformCache = std::move(other.uniformCache);

    other.tag = "";
    other.vertPath = "";
    other.fragPath = "";
    other.vertexSource = "";
    other.fragmentSource = "";
    other.fragmentHandle = -1;
    other.vertexHandle = -1;
    other.shaderProgramHandle = -1;
    other.uniformCache.clear();
    return *this;
}

Shader::~Shader() {
    LOG_WARN("Deleted shader[{0}]", tag);
    glDeleteProgram(shaderProgramHandle);
}

//default first = false
void Shader::CleanAndChange(std::string _tag, bool first) {
    LOG_INFO("Shader CleanAndChange {}", _tag);
    //don't recompile the shader if its already the right shader
    if (!first && tag == _tag) {
        std::cout << "Shader is already using " << _tag << std::endl;
        return;
    }

    //delete currently created shader program
    glDeleteProgram(shaderProgramHandle);

    //create new shader program with the new shader source
    vertPath = path + "vert.glsl";
    fragPath = path + "frag.glsl";
    Init();
}

void Shader::Init() {
    LOG_INFO("Initializing Shader {}, path={}", tag, path);
    readFile(vertPath, vertexSource);       //fileUtil.h
    readFile(fragPath, fragmentSource);     // -
    
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
        LOG_ERROR("Vertex Shader compilation failed {}", infoLog);
    } else {
        LOG_INFO("Vertex Shader compilation succeeded");
    }

    //FRAGMENT SHADER
    source = fragmentSource.c_str();
    
    fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentHandle, 1, &source, NULL);
    glCompileShader(fragmentHandle);
    glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexHandle, 512, NULL, infoLog);
        LOG_ERROR("Fragment Shader compilation failed {}", infoLog);
    } else {
        LOG_INFO("Frament Shader compilation succeeded"); 
    }
    
    //LINK PROGRAM
    shaderProgramHandle = glCreateProgram();
    glAttachShader(shaderProgramHandle, vertexHandle);
    glAttachShader(shaderProgramHandle, fragmentHandle);
    glLinkProgram(shaderProgramHandle);
    glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramHandle, 512, NULL, infoLog);
        LOG_ERROR("Shader Program linking failed");
    } else {
        LOG_INFO("Shader Program linking succeeded");
    }
    glDeleteShader(fragmentHandle);
    glDeleteShader(vertexHandle);
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

int Shader::GetLocation(const char* name) {
    glUseProgram(shaderProgramHandle);
    if (uniformCache.find(name) != uniformCache.end()) {
        return uniformCache.at(name);
    }
    int location = glGetUniformLocation(shaderProgramHandle, name);
    if (location == -1) {
        //LOG_ERROR("Requested uniform {0} not found in {1}", name, tag);
        return -1;
    }
    uniformCache.emplace(name, location);
    return uniformCache.at(name); 
}
}
