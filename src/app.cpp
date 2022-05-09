#include <LTR/ltr_mbdr_gl.h>
#include <iostream>
#include <string>

#include <LTR/ltr_file.h>

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
    void OnStart() override
    {

    }

    void OnUpdate(float deltaTime) override
    {

    }

    void OnLog(std::string log) override
    {
        std::cout << log;
    }
    void OnLogWarning(std::string context, std::string err) override
    {
        std::cout << std::endl << m_AppName << " WARNING by " + context + " when " + err + " ";
    }
    void OnLogError(std::string context, std::string err) override
    {
        std::cout << std::endl << m_AppName << " ERROR by " + context + " when " + err + " ";
    }
};


int main(int argc, char** argv)
{
    Space3D app;

    if (!app.ConstructApp())
        app.Run();

    std::cout << std::endl << "Press enter to quit: ";
    std::cin.get();

    return 0;
}