#define _CRT_SECURE_NO_WARNINGS
#include "Platform.h"
#include "RenderingInterface.h"
#include "Scene.h"
#include "Camera.h"
#include "Application.h"


int main(int argc, char **argv) {
    Platform& P = Platform::GetInstance();
    P.InitializeWindow(1440, 900, "Stochastic Rasterization x86 OpenGL");
   
    Application& App = Application::Get();
    App.mPhongShader = LoadShaders("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/fragment.glsl");
    GLuint Program = App.mPhongShader.GetProgramID();

    Scene& scene = Scene::Get();
    scene.LoadObjFromFile("Assets/sponza.obj", "Assets/");
    Camera& Cam = Camera::Get();
    Cam.SetProjMatrix(45.f, (float)P.GetWindowWidth() / (float)P.GetWindowHeight(), 0.1f, 2000.f);
    Cam.SetViewMatrix(glm::vec3(0.f, 2.f, 30.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    for (std::size_t i = 0; i < scene.shapes.size(); ++i) {
        tinyobj::mesh_t current_mesh = scene.shapes[i].mesh;
        if (current_mesh.material_ids[0] >= 0) {
            tinyobj::material_t& material = scene.materials[current_mesh.material_ids[0]];
            glUniform4f(glGetUniformLocation(Program, "Kd_Diffuse"), material.ambient[0], material.ambient[1], material.ambient[2], 1.f);
        }
    }
    glEnable(GL_DEPTH_TEST);
    SDL_Event event;
    bool bShouldQuit = false;
    while (!bShouldQuit) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.RenderScene(Program);
        SDL_GL_SwapWindow(P.GetSDLWindow());
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                bShouldQuit = true;
                break;
            }
            Cam.UpdateCamera(event);
        }
    }
    return 0;
}
