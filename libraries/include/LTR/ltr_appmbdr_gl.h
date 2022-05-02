#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

/* Lother App Embedder for Open GL */
class LTRAppEmbedderGL
{
#pragma region App Base
public:
    LTRAppEmbedderGL()
    {
        // Initialize default values
        m_Window = NULL;
        
        m_AppName = (char *)"New Open GL App";
        m_ScreenWidth = 80;
        m_ScreenHeight = 30;
    }

    // Create window and setup GLFW and GLEW
    int ConstructApp()
    {
        // Generate window
        if (!glfwInit())
        {
            OnLogError(-1, "GLFW could not init.");
            return -1;
        }

        m_Window = glfwCreateWindow(m_ScreenWidth, m_ScreenHeight, m_AppName, NULL, NULL);
        if (!m_Window)
        {
            glfwTerminate();
            OnLogError(-1, "GLFW could not create window.");
            return -1;
        }
        
        // Make the window the current context
        glfwMakeContextCurrent(m_Window);

        // Init glew
        if (glewInit() != GLEW_OK)
        {
            OnLogError(-1, "GLEW could not init.");
            return -1;
        }

        return 0;
    }

    // App Runtime Execution
    void Run()
    {
        // Focal app start
        AppStart();
        
        // Call user start
        OnStart();
        OnLogWarning("App Started.");

        // Frame update
        while (!glfwWindowShouldClose(m_Window))
        {
            // Local frame update
            AppFrameUpdate();
        }

        OnTerminate();
        OnLogWarning("App Terminated.");

        glfwTerminate();
    }

    ~LTRAppEmbedderGL()
    {
    }
    #pragma endregion

#pragma region App Runtime
private:
    void AppStart()
    {
        float positions[6] = { -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f };

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void AppFrameUpdate()
    {
        // Clear buffer
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawArrays(GL_TRIANGLES, 0, 3);


        // Call user update
        OnUpdate((float)glfwGetTime());

        // Swap Buffers
        glfwSwapBuffers(m_Window);
        // Poll for and process events
        glfwPollEvents();
    }
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