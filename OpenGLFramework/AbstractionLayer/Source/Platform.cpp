#include "Platform.h"
#include "UnitTest.h"

void glCheckError(std::string Description) {
    GLenum Status = glGetError();
    if (Status != GL_NO_ERROR) {
        PlatformUtils::Logging::LogError("OpenGL error: %i | %s\n", Status, Description);
#ifdef DEBUG
        abort();
#endif
    }
}

void WindowSizeCallBack(SDL_Window* Window, int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}

void GeneralPlatform::ShowWindow() const
{
#ifdef _DEBUG
    assertf(Window, "SDL window null");
    SDL_ShowWindow(Window);
#else
    SDL_ShowWindow(Window);
#endif
}

void GeneralPlatform::HideWindow() const
{
#ifdef _DEBUG
    assertf(Window, "SDL window null");
    SDL_HideWindow(Window);
#else
    SDL_HideWindow(Window);
#endif
}

bool GeneralPlatform::InitializeWindow(int nWidth, int nHeight, const char* szWindowTitle) const
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        PlatformUtils::Logging::LogError("Couldn't initialize SDL");
    atexit(SDL_Quit);
    stbi_set_flip_vertically_on_load(true);
    SDL_GL_LoadLibrary(nullptr);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    Window = SDL_CreateWindow(
        szWindowTitle,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        nWidth, nHeight, SDL_WINDOW_OPENGL
        );
    if (Window == nullptr) {
        PlatformUtils::Logging::LogError("Couldn't set video mode");
    }
    MainContext = SDL_GL_CreateContext(Window);
    if (MainContext == nullptr)
        PlatformUtils::Logging::LogError("Failed to create OpenGL context");
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    SDL_GL_SetSwapInterval(1);
    glViewport(0, 0, nWidth, nHeight);
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glCheckError("Initialization");
    PlatformUtils::Logging::LogError("%s\n", glGetString(GL_VERSION));
    PlatformUtils::Logging::LogError("%s\n", glGetString(GL_VENDOR));
    PlatformUtils::Logging::LogError("%s\n", glGetString(GL_RENDERER));

    WindowWidth = nWidth;
    WindowHeight = nHeight;
    return true;
}

SDL_Window* GeneralPlatform::GetSDLWindow() const
{
#ifdef _DEBUG
    assertf(Window, "SDL window null");
#endif
    return Window;
}

SDL_GLContext GeneralPlatform::GetSDLContext() const
{
    return MainContext;
}

void GeneralPlatform::DestroyWindow() const
{
    SDL_Quit();
}
