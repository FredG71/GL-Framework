#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Platform.h"

class Camera {
public:
    static Camera& Get()
    {
        static Camera Instance;
        return Instance;
    }
    inline void SetViewMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
        ViewMatrix = glm::lookAt(eye, center, up);
    }
    inline void SetProjMatrix(float FOV, float AspectRatio, float NearPlane, float FarPlane) {
        ProjMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
    }
    void UpdateCamera(SDL_Event event);
    glm::mat4 ViewMatrix;
    glm::mat4 ProjMatrix;
    Camera() :
        ViewMatrix(1.f), ProjMatrix(1.f)
    {}
};
