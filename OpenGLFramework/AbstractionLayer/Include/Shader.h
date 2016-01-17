#pragma once
#include "RenderingInterface.h"

class Shader {
public:
    void CompileShader(std::string VertexSource, std::string FragmentSource);//(std::string VertexPath, std::string FragmentPath);
    void Bind() {
        glUseProgram(Program);
    }
    GLuint GetProgramID() const {
        return Program;
    }
private:
    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint Program;
};

template<typename T>
std::string OpenShader(T&& FilePath);
Shader LoadShaders(std::string VertexShader, std::string FragmentShader);
