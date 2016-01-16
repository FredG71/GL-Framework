#pragma once
#include "Debug.h"
#include "Logging.h"
#include "typedef.h"
#include "glad.h"
#include "SDL/SDL.h"
#include "Shaders.h"

extern char szApplicationTitle[];
void glCheckError(std::string Description);

class Application {
public:
    static Application& Get() {
        static Application Instance;
        return Instance;
    }
    SDL_Window* GetWindow() const {
        return Window;
    }
    int32 GetScreenHeight() const {
        return nScreenHeight;
    }
    int32 GetScreenWidth() const {
        return nScreenWidth;
    }
    int32 InitGL(int32 nWidth, int32 nHeight);
    bool DestroyWindow();
    Application() :
        Window(nullptr),
        nScreenWidth(0),
        nScreenHeight(0)
    {}
    Application(const Application&)         = default;
    Application& operator=(Application&)    = default;
    ~Application() {
        DestroyWindow();
    }
private:
    SDL_Window* Window;
    SDL_GLContext MainContext;
    int32 nScreenWidth;
    int32 nScreenHeight;
};
