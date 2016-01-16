#pragma once
#include <fstream>
#include "Application.h"

class Shader {
public:
    void CompileShader(std::string VertexSource, std::string FragmentSource);
    void Bind() {
        glUseProgram(Program);
    }
    GLuint GetProgramID() const {
        return Program;
    }
private:
    GLuint VertexShader     = -1;
    GLuint FragmentShader   = -1;
    GLuint Program          = -1;
};

template<typename T>
std::string OpenShader(T&& FilePath);
Shader LoadShaders(std::string VertexShader, std::string FragmentShader);
