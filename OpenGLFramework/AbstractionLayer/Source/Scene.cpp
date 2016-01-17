#include "Scene.h"
#include "Camera.h"

Map TextureDictionary{};

void Texture::LoadTexture(std::string Path) {
    if (Path.empty()) {
        std::cout << "Loading empty texture!\n" << std::endl;
        return;
    }
    Map::const_iterator It = TextureDictionary.find(Path);
    if (It != TextureDictionary.end()) {
        Id = It->second;
        return;
    }
    else {
        if (!Id) {
            glGenTextures(1, &Id);
        }
        glBindTexture(GL_TEXTURE_2D, Id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        int nWidth, nHeight, nComp;
        auto Texels = stbi_load(Path.c_str(), &nWidth, &nHeight, &nComp, STBI_rgb_alpha);
        if (!Texels) {
            std::cout << "Texels are NULL!\n" << std::endl;
            return;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, Texels);
        stbi_image_free(Texels);
        TextureDictionary.insert(std::make_pair(Path, Id));
    }
}

void Mesh::Build() {
    if (!VBO) {
        glGenBuffers(1, &VBO);
    }
    if (!VAO) {
        glGenVertexArrays(1, &VAO);
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

    // Assuming layout directives are used for pos, normals and UVs!
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::nx));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::u));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Scene::LoadObjFromFile(std::string Path, std::string MtlPath) {
    if (Path.empty() || MtlPath.empty()) {
        abort();
    }
    std::string err = tinyobj::LoadObj(shapes, materials, Path.c_str(), MtlPath.c_str());
    if (!err.empty()) {
        abort();
    }
    Meshes.resize(shapes.size());
    for (uint32 i = 0; i < shapes.size(); ++i) {
        Meshes[i].Vertices.resize(
            shapes[i].mesh.indices.size());
        for (uint32 j = 0; j < shapes[i].mesh.indices.size(); ++j) {
            int Index = shapes[i].mesh.indices[j];
            Meshes[i].Vertices[j].x = shapes[i].mesh.positions[3 * Index + 0];
            Meshes[i].Vertices[j].y = shapes[i].mesh.positions[3 * Index + 1];
            Meshes[i].Vertices[j].z = shapes[i].mesh.positions[3 * Index + 2];

            Meshes[i].Vertices[j].nx = shapes[i].mesh.normals[3 * Index + 0];
            Meshes[i].Vertices[j].ny = shapes[i].mesh.normals[3 * Index + 1];
            Meshes[i].Vertices[j].nz = shapes[i].mesh.normals[3 * Index + 2];

            Meshes[i].Vertices[j].u = shapes[i].mesh.texcoords[2 * Index + 0];
            Meshes[i].Vertices[j].v = shapes[i].mesh.texcoords[2 * Index + 1];
        }
        Meshes[i].Indices = shapes[i].mesh.indices;
        tinyobj::mesh_t current_mesh = shapes[i].mesh;
        if (current_mesh.material_ids[0] >= 0) {
            tinyobj::material_t& material = materials[current_mesh.material_ids[0]];
            std::string DiffuseMap = "Assets/" + material.diffuse_texname;
            Meshes[i].mTexture = new Texture();
            Meshes[i].mTexture->LoadTexture(DiffuseMap);
        }
    }
    for (uint32 i = 0; i < shapes.size(); ++i) {
        Meshes[i].Build();
    }
}

void Scene::RenderScene(GLuint ProgramID) {
    Camera& Cam = Camera::Get();
    for (auto& i : Meshes) {
        if (i.mTexture) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, i.mTexture->Id);
        }
        glUniformMatrix4fv(glGetUniformLocation(ProgramID, "MVP"), 1, GL_FALSE, glm::value_ptr(Cam.ProjMatrix * Cam.ViewMatrix));
        glBindVertexArray(i.VAO);
        glDrawArrays(GL_TRIANGLES, 0, i.Vertices.size());
    }
}
