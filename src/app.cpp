#include <LTR/ltr_mbdr_gl.h>
#include <iostream>
#include <string>

class Space3D : public ltr::AppEmbedder
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

    void OnLog(std::string log)
    {
        std::cout << log;
    }
    void OnLogWarning(std::string context, std::string err)
    {
        std::cout << std::endl << "=> WARNING by " + context + ", " + err + " ";
    }
    void OnLogError(std::string context, std::string err)
    {
        std::cout << std::endl << "=> ERROR by " + context + ", " + err + " ";
    }
};


int main(int argc, char** argv)
{
    Space3D app;

    if (!app.ConstructApp())
        app.Run();

    std::cin.get();

    return 0;
}