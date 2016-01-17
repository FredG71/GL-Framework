#pragma once
#include "Shader.h"

class Application {
public:
    static Application& Get() {
        static Application Instance;
        return Instance;
    }
    Shader mPhongShader;
};
