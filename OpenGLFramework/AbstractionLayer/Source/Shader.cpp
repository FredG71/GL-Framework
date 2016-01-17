#include "Shader.h"

template<typename T>
std::string OpenShader(T&& FilePath)
{
    std::string RetVal = {};
    std::ifstream File(std::forward<T>(FilePath));
    if (File.is_open())
    {
        std::string TempByte;
        while (!File.eof())
        {
            std::getline(File, TempByte);
            RetVal.append(TempByte + "\n");
        }
        File.close();
    }
    return RetVal;
}

Shader LoadShaders(std::string VertexShader, std::string FragmentShader) {
    Shader RetVal{};
    std::string VertexSource = OpenShader(VertexShader);
    std::string FragmentSource = OpenShader(FragmentShader);

    RetVal.CompileShader(VertexSource, FragmentSource);
    return RetVal;
}

void Shader::CompileShader(std::string VertexSource, std::string FragmentSource) {

    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar const* Type = FragmentSource.c_str();
    GLint nLength = FragmentSource.length();
    glShaderSource(FragmentShader, 1, &Type, &nLength);
    glCompileShader(FragmentShader);

    GLint nSuccess = 0;
    GLchar Log[512];
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &nSuccess);
    if (!nSuccess)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, Log);
        std::cout << "FRAGMENT SHADER FAILED: " << Log << std::endl;
    }

    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    Type = VertexSource.c_str();
    nLength = VertexSource.length();
    glShaderSource(VertexShader, 1, &Type, &nLength);
    glCompileShader(VertexShader);

    nSuccess = 0;
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &nSuccess);
    if (!nSuccess)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, Log);
        std::cout << "VERTEX SHADER FAILED: " << Log << std::endl;
    }

    Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);

    glLinkProgram(Program);
    nSuccess = 0;
    glGetProgramiv(Program, GL_LINK_STATUS, &nSuccess);
    if (!nSuccess)
    {
        glGetProgramInfoLog(Program, 512, NULL, Log);
        std::cout << "PROGRAM LINK FAILED: " << Log << std::endl;
    }
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    Bind();
}
