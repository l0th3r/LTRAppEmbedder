#include <LTR/ltr_appmbdr_gl.h>
#include <iostream>

class Space3D : public app_embedder_gl
{
public:
    Space3D()
    {
        m_AppName = (char*)"Lother Viewer";
    }
private:
    void OnStart()
    {
    }

    void OnUpdate(float deltaTime)
    {
        
    }

    void HandleError(int err, const char* msg)
    {
        std::cerr << m_AppName << " ERR: " << err << " MSG: " << msg << std::endl;
    }
    void HandleWarning(const char* msg)
    {
        std::cerr << m_AppName << " WARNING: " << msg << std::endl;
    }
};


int main(int argc, char** argv)
{
    Space3D app;

    if (!app.ConstructApp(500, 500))
        app.Start();

    std::cin.get();

    return 0;
}