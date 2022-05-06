#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

/* Lother App Embedder for Open GL */
class LTR_Embedder
{
#pragma region App Base
public:
    LTR_Embedder();

    // Create window and setup GLFW and GLEW
    int ConstructApp();

    // App Runtime Execution
    void Run();

    ~LTR_Embedder();
    #pragma endregion

#pragma region App Runtime
private:
    void AppStart();
    void AppFrameUpdate();

protected:
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& sVertex, const std::string& sFragment);
#pragma endregion

#pragma region Class Static Methods

#pragma endregion

#pragma region App Overridable
protected:
    // App user overriding events
    virtual void OnStart()=0;
    virtual void OnUpdate(float deltaTime)=0;
    virtual void OnTerminate(){};

    // Logs
    virtual void OnLogWarning(const char* msg) {};
    virtual void OnLogError(int err, const char* msg) {};
#pragma endregion

#pragma region App Variables
protected:
    GLFWwindow* m_Window;
public:
    char* m_AppName;
    int m_ScreenWidth;
    int m_ScreenHeight;
private:
    unsigned int m_shader;
#pragma endregion
};