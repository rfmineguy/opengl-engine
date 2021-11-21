#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader() = default;
    Shader(std::string tag);
    
    //delete copy ctor
    Shader(const Shader&) = delete;
    //delete copy assignment operator
    Shader& operator=(Shader&) = delete;
    
    //move ctor
    Shader(Shader&& other);
    //move assignment operator
    Shader& operator=(Shader&& other);

    ~Shader();
    void CleanAndChange(std::string tag, bool first = false);
    void Init();
    void Bind();
    void Unbind();

//Uniform Seters
public:
    void Set1f(const char* name, float a) ;
    void Set2f(const char* name, float a, float b) ;
    void Set3f(const char* name, float a, float b, float c) ;
    void Set4f(const char* name, float a, float b, float c, float d) ;
    
    void Set4fv(const char* name, glm::mat4 matrix);

    void Set1i(const char* name, int a);

private:
    int GetLocation(const char* name);

//Member variables
private:
    std::string vertPath;
    std::string fragPath;
    std::string vertexSource;
    std::string fragmentSource;

    unsigned int fragmentHandle;
    unsigned int vertexHandle;

    std::map<const char*, int> uniformCache;

public:
    unsigned int shaderProgramHandle;
    std::string tag;
};
