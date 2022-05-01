#include <LTR/ltr_appmbdr_gl.h>
#include <iostream>

class Space3D : public LTRAppEmbedderGL
{
public:
    Space3D()
    {
        m_AppName = (char*)"Lother Viewer";
        m_ScreenHeight = 500;
        m_ScreenWidth = 500;
    }
private:
    void OnStart()
    {

    }

    void OnUpdate(float deltaTime)
    {
        
    }

    void OnLogWarning(const char* msg)
    {
        std::cerr << m_AppName << " WARNING: " << msg << std::endl;
    }
    void OnLogError(int err, const char* msg)
    {
        std::cerr << m_AppName << " ERR: " << err << " MSG: " << msg << std::endl;
    }
};


int main(int argc, char** argv)
{
    Space3D app;

    if (!app.ConstructApp())
        app.Start();

    std::cin.get();

    return 0;
}