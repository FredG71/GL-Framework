#pragma once
#include "tinyformat.h"
#include <Windows.h>
class Logging
{
public:
    template<typename ...Args>
    static void Printf(Args&&... Params)
    {
        SetConsoleTextAttribute(stdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        tinyformat::printf(std::forward<Args>(Params)...);
    }
    template<typename ...Args>
    static void LogTests(Args&&... Params)
    {
        SetConsoleTextAttribute(stdout, FOREGROUND_GREEN);
        tinyformat::printf(std::forward<Args>(Params)...);
    }
    template<typename ...Args>
    static void LogError(Args&&... Params)
    {
        SetConsoleTextAttribute(stdout, FOREGROUND_RED);
        tinyformat::printf(std::forward<Args>(Params)...);
    }
    template<typename ...Args>
    static void LogWarning(Args&&... Params)
    {
        SetConsoleTextAttribute(stdout, FOREGROUND_RED | FOREGROUND_GREEN);
        tinyformat::printf(std::forward<Args>(Params)...);
    }
};
