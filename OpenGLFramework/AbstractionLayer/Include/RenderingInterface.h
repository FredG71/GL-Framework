#pragma once
#include "Platform.h"
#include "Shader.h"
#include <vector>
#ifdef _DEBUG
#include <ctime>
#endif
#include <tiny_obj_loader.h>

class GeneralRenderingInterface {
public:
protected:
    GeneralRenderingInterface()                                         = default;
    ~GeneralRenderingInterface()                                        = default;
    GeneralRenderingInterface(const GeneralRenderingInterface&)         = default;
    GeneralRenderingInterface(GeneralRenderingInterface&&)              = default;
    GeneralRenderingInterface& operator=(GeneralRenderingInterface&)    = default;
    GeneralRenderingInterface& operator=(GeneralRenderingInterface&&)   = default;
};

/*Consider using Direct3D instead of GL for windows and change this to Mac or Linux defines*/
#if defined _WIN32 || defined _WIN64
class GLRenderingInterface : public GeneralRenderingInterface {
public:
    static GLRenderingInterface& GetInstance()
    {
        static GLRenderingInterface Instance;
        return Instance;
    }
private:
};
#endif
using RenderingInterface = GLRenderingInterface;

#ifdef D3D11
class Direct3DRenderingInterface : public GeneralRenderingInterface{

};
using RenderingInterface = Direct3DRenderingInterface;
#endif
