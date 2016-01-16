#pragma once
#include "Application.h"
#include <string>
#include <vector>
#include <tiny_obj_loader.h>
#include <glm\vec3.hpp>

class Scene {
public:
    static Scene& Get() {
        static Scene Instance;
        return Instance;
    }
    bool LoadObjFromFile(std::string FileName, std::string MtlPath);
    inline bool DrawTestTriangle() {
        static GLuint triVAO;
        GLuint triVBO;
        Shader Phong = LoadShaders(R"(Source/Shaders/PhongShader.vert)",
            R"(Source/Shaders/PhongShader.frag)");
        glUseProgram(Phong.GetProgramID());
        glGenVertexArrays(1, &triVAO);
        glGenBuffers(1, &triVBO);
        glBindBuffer(GL_ARRAY_BUFFER, triVBO);
        glBindVertexArray(triVAO);

        static const GLfloat vertData[] = {
               -1.0f, -1.0f, 0.0f,
               1.0f, -1.0f, 0.0f,
               0.0f,  1.0f, 0.0f,
            };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);
        // Pass vertex information to position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glCheckError("DrawTestTriangle");
        return true;
    }
private:
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    GLuint SceneVAO;
    GLuint SceneVBO;
    GLuint SceneIBO;
};
