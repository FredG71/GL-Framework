#include "Application.h"

Application App;
int main(int argc, char **argv)
{
    App = Application::Get();
    App.InitGL(1024, 768);
    return 0;
}
