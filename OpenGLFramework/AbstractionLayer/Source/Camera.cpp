#include "Camera.h"

void Camera::UpdateCamera(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_w:
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(-10.5f, 0.f, 0.f));
        break;
    case SDLK_a:
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.f, 0.f, 10.5f));
        break;
    case SDLK_d:
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.f, 0.f, -10.5f));
        break;
    case SDLK_s:
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(10.5f, 0.f, 0.f));
        break;
    case SDLK_e:
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.f, 10.5f, 0.f));
        break;
    case SDLK_q:
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.f, -10.5f, 0.f));
        break;
    case SDLK_UP:
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(5.f), glm::vec3(-1.f, 0.f, 0.f));
        break;
    case SDLK_DOWN:
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(5.f), glm::vec3(1.f, 0.f, 0.f));
        break;
    case SDLK_RIGHT:
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(5.f), glm::vec3(0.f, 1.f, 0.f));
        break;
    case SDLK_LEFT:
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(-5.f), glm::vec3(0.f, 1.f, 0.f));
        break;
    }
}
