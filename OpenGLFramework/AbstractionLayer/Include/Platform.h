#pragma once
#if defined _WIN32 || defined _WIN64
    #include <glad.h>
    #include <SDL\SDL.h>
    #undef APIENTRY // Suppress redefinition /*Consider using Direct3D if on Windows shortly*/
#else
    #include <glad.h>
    #include <SDL\SDL.h>
#endif

#include <cstdint>
#include <fstream>
#include <cstring>
#include <cfloat>
#include <cassert>
#include "tinyformat.h"
#include <stb_image.h>
#include <stb_image_write.h>
#include "typedef.h"

enum class EWindowMode : std::uint8_t
{
    EFullScreen,
    EWindowed,
    EWindowedFullScreen,
    EModeUnSpecified
};

#if defined _WIN32 || defined _WIN64
    #define UNICODE
    #include <Windows.h>
#else
    using TCHAR = wchar_t;
#endif
class GeneralPlatform
{
public:
    virtual void ShowWindow()                   const;

    virtual void UpdateWindow()                 const           = 0;
    virtual bool InitializeWindow(int, int, 
                                const char*)    const           = 0;

    virtual void PaintWindow()                  const           = 0;
    virtual bool IsMaximized()                  const           = 0;
    virtual bool IsMinimized()                  const           = 0;
    virtual EWindowMode GetWindowMode()         const           = 0;
    virtual void* GetWindowHandle()             const           = 0;
    virtual const TCHAR* GetWindowTitle()       const           = 0;
    virtual void DestroyWindow()                const           = 0;
    virtual std::uint32_t GetWindowWidth()      const           = 0;
    virtual std::uint32_t GetWindowHeight()     const           = 0;
    virtual bool IsWindowFocus()                const           = 0;
    virtual void IsVisible()                    const           = 0;
    virtual void HideWindow()                   const           = 0;
    virtual SDL_Window* GetSDLWindow()          const           = 0;
    virtual SDL_GLContext GetSDLContext()       const           = 0;

    virtual bool MoveWindowTo(std::int32_t X, std::int32_t Y)   = 0;
    virtual void Minimize()                                     = 0;
    virtual void Maximize()                                     = 0;
    virtual void Restore()                                      = 0;
    virtual void SetWindowMode(EWindowMode)                     = 0;
    virtual void SetWindowFocus()                               = 0;
    virtual void EnableWindow()                                 = 0;
    virtual void DisableWindow()                                = 0;
    virtual void SetOpacity(const float)                        = 0;
    virtual void SetWindowTitle(const TCHAR* szText)            = 0;
    virtual void SetIsMaximized(bool bMaximize)                 = 0;
    virtual void SetIsMinimized(bool bMinimized)                = 0;

protected:
    char* WindowTitle;
    mutable SDL_Window* Window;
    mutable SDL_GLContext MainContext;
    mutable uint32 WindowWidth;
    mutable uint32 WindowHeight;
    GeneralPlatform()                                   = default;
    GeneralPlatform(const GeneralPlatform&)             = default;
    GeneralPlatform& operator=(const GeneralPlatform&)  = default;
    GeneralPlatform& operator=(GeneralPlatform&&)       = default;
    GeneralPlatform(GeneralPlatform&&)                  = default;
    virtual ~GeneralPlatform()                          = default;
};

class GeneralPlatformUtils
{
public:
    static void LaunchDebuggingConsole()
    {
        // Implement...
    }
    static std::uint64_t GetCurrentProcessID()
    {
        // Implement...
    }
protected:
    GeneralPlatformUtils()                                          = delete;
    GeneralPlatformUtils(const GeneralPlatformUtils&)               = delete;
    GeneralPlatformUtils& operator=(const GeneralPlatformUtils&)    = delete;
    GeneralPlatformUtils& operator=(GeneralPlatformUtils&&)         = delete;
    GeneralPlatformUtils(GeneralPlatformUtils&&)                    = delete;
    virtual ~GeneralPlatformUtils()                                 = delete;
};

#if defined (_WIN32) || (_WIN64)
#include <Windows.h>
class PlatformWindows : public GeneralPlatform
{
public:

    virtual void ShowWindow()                         const         override
    {
        GeneralPlatform::ShowWindow();
    }
    virtual void HideWindow()                         const         override
    {
        GeneralPlatform::HideWindow();
    }
    virtual bool InitializeWindow(int nWidth, int nHeight,
                                  const char* Title)  const         override
    {
        return GeneralPlatform::InitializeWindow(nWidth, nHeight, Title);
    }
    virtual SDL_Window* GetSDLWindow()                const         override 
    { 
        return GeneralPlatform::GetSDLWindow(); 
    }
    virtual SDL_GLContext GetSDLContext()             const         override
    {
        return GeneralPlatform::GetSDLContext();
    }
    virtual void DestroyWindow()                      const         override
    {
        GeneralPlatform::DestroyWindow();
    }

    virtual void UpdateWindow()                       const         override {}
    virtual void PaintWindow()                        const         override {}
    virtual void IsVisible()                          const         override {}

    virtual bool IsMaximized()                        const         override { return true; }
    virtual bool IsMinimized()                        const         override { return true; }
    virtual bool IsWindowFocus()                      const         override { return true; }

    virtual const TCHAR* GetWindowTitle()             const         override { return WindowTitle; }
    virtual void* GetWindowHandle()                   const         override { return nullptr; }
    virtual EWindowMode GetWindowMode()               const         override { return EWindowMode::EFullScreen; }
    virtual std::uint32_t GetWindowWidth()            const         override { return WindowWidth; }
    virtual std::uint32_t GetWindowHeight()           const         override { return WindowHeight; }

    virtual bool MoveWindowTo(std::int32_t X, std::int32_t Y)       override { return true; }
    virtual void Minimize()                                         override {}
    virtual void Maximize()                                         override {}
    virtual void Restore()                                          override {}
    virtual void SetWindowMode(EWindowMode)                         override {}
    virtual void SetWindowFocus()                                   override {}
    virtual void EnableWindow()                                     override {}
    virtual void DisableWindow()                                    override {}
    virtual void SetOpacity(const float)                            override {}
    virtual void SetWindowTitle(const TCHAR* szText)                override {}
    virtual void SetIsMaximized(bool bMaximize)                     override {}
    virtual void SetIsMinimized(bool bMinimize)                     override {}


    static PlatformWindows& GetInstance()
    {
        static PlatformWindows Instance;
        return Instance;
    }

protected:
    HWND hWindowHandle;
    std::int32_t nCmdShow;
    HINSTANCE hWindowInstance;
    const WCHAR* szWindowTitle;
    const WCHAR* szWindowClass;
    EWindowMode WindowMode;
    bool bMaximized;
    bool bMinimized;

    PlatformWindows()                                       = default;
    PlatformWindows(const PlatformWindows&)                 = default;
    PlatformWindows& operator=(const PlatformWindows&)      = default;
    PlatformWindows& operator=(PlatformWindows&&)           = default;
    PlatformWindows(PlatformWindows&&)                      = default;
    virtual ~PlatformWindows()                  override    = default;
};

class PlatformWindowsUtils : public GeneralPlatformUtils
{
public:
    class Logging
    {
    public:
        template<typename ...Args>
        static void Printf(Args&&... Params)
        {
            //@TODO: Typedef stdout for each specific platform?
            SetConsoleTextAttribute(stdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            tinyformat::printf(std::forward<Args>(Params)...);
        }
        template<typename ...Args>
        static void LogTests(Args&&... Params)
        {
            //@TODO: Typedef stdout for each specific platform?
            SetConsoleTextAttribute(stdout, FOREGROUND_GREEN);
            tinyformat::printf(std::forward<Args>(Params)...);
        }
        template<typename ...Args>
        static void LogError(Args&&... Params)
        {
            //@TODO: Typedef stdout for each specific platform?
            SetConsoleTextAttribute(stdout, FOREGROUND_RED);
            tinyformat::printf(std::forward<Args>(Params)...);
        }
        template<typename ...Args>
        static void LogWarning(Args&&... Params)
        {
            //@TODO: Typedef stdout for each specific platform?
            SetConsoleTextAttribute(stdout, FOREGROUND_RED | FOREGROUND_GREEN);
            tinyformat::printf(std::forward<Args>(Params)...);
        }
    };
protected:
    PlatformWindowsUtils()                                          = delete;
    PlatformWindowsUtils(const PlatformWindowsUtils&)               = delete;
    PlatformWindowsUtils& operator=(const PlatformWindowsUtils&)    = delete;
    PlatformWindowsUtils& operator=(PlatformWindowsUtils&&)         = delete;
    PlatformWindowsUtils(PlatformWindowsUtils&&)                    = delete;
    virtual ~PlatformWindowsUtils()                                 = delete;
private:
};

using PlatformUtils         = PlatformWindowsUtils;
using Platform              = PlatformWindows;
#endif
