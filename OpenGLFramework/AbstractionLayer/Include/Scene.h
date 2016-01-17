#pragma once
#include "Platform.h"
#include <vector>
#include <map>
#include "tiny_obj_loader.h"

struct Comparator {
    bool operator() (std::string lhs, std::string rhs) const {
        return lhs.compare(rhs) < 0;
    }
};
using Map = std::map<std::string, GLuint, Comparator>;
extern Map TextureDictionary;

class Texture {
public:
    GLint Width;
    GLint Height;
    GLuint Id;
    void LoadTexture(std::string);

    Texture() :
        Width(0), Height(0), Id(0)
    {}
};

class Mesh {
public:
    struct Vertex {
        // Position
        float x;
        float y;
        float z;
        // Normal
        float nx;
        float ny;
        float nz;
        // UV
        float u;
        float v;
    };
    GLuint VAO;
    GLuint VBO;
    std::vector<Vertex> Vertices;
    std::vector<uint32> Indices;
    Texture* mTexture;
    void Build();

    Mesh() :
        VAO(0), VBO(0), mTexture(nullptr)
    {}
};

class Scene {
public:
    static Scene& Get()
    {
        static Scene Instance;
        return Instance;
    }
    std::vector<Mesh> Meshes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    void LoadObjFromFile(std::string Path, std::string MtlPath);
    void RenderScene(GLuint ProgramID);
};
