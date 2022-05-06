#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

/* Lother App Embedder for Open GL */
class LTREmbedderGL
{
#pragma region App Base
public:
    LTREmbedderGL();

    // Create window and setup GLFW and GLEW
    int ConstructApp();

    // App Runtime Execution
    void Run();

    ~LTREmbedderGL();
    #pragma endregion

#pragma region App Runtime
private:
    void AppStart();
    void AppFrameUpdate();
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

#pragma region App Settings
protected:
    GLFWwindow* m_Window;
public:
    char* m_AppName;
    int m_ScreenWidth;
    int m_ScreenHeight;
#pragma endregion
};