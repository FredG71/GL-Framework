#include "Application.h"
#include "Scene.h"

char szApplicationTitle[] = "Stochastic Rasterization x86 OpenGL";

void glCheckError(std::string Description) {
    GLenum Status = glGetError();
    if (Status != GL_NO_ERROR) {
        Logging::LogError("OpenGL error: %i | %s\n", Status, Description);
#ifdef DEBUG
        abort();
#endif
    }
}


static void sdl_die(const char * message) {
    Logging::LogError("%s: %s\n", message, SDL_GetError());
    exit(2);
}
int Application::InitGL(int32 nWidth, int32 nHeight){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        sdl_die("Couldn't initialize SDL");
    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(nullptr);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    Window = SDL_CreateWindow(
        szApplicationTitle,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        nWidth, nHeight, SDL_WINDOW_OPENGL
        );
    if (Window == nullptr) {
        sdl_die("Couldn't set video mode");
    }
    MainContext = SDL_GL_CreateContext(Window);
    if (MainContext == nullptr)
        sdl_die("Failed to create OpenGL context");
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    SDL_GL_SetSwapInterval(1);
    glViewport(0, 0, nWidth, nHeight);
    glClearDepth(0.0);
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glCheckError("Initialization");
    Logging::LogError("%s\n", glGetString(GL_VERSION));
    Logging::LogError("%s\n", glGetString(GL_VENDOR));
    Logging::LogError("%s\n", glGetString(GL_RENDERER));

    SDL_Event event;
    bool bShouldQuit = false;
    Scene& scene = Scene::Get();
    while (!bShouldQuit) {
        SDL_GL_SwapWindow(Window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.DrawTestTriangle();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                bShouldQuit = true;
            }
        }
    }
    return 0;
}

bool Application::DestroyWindow() {
    return true;
}
