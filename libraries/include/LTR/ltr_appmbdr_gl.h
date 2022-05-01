#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* Lother App Embedder for Open GL */
class LTRAppEmbedderGL
{
public:
    LTRAppEmbedderGL()
    {
        // Initialize settings and values
        m_Window = NULL;
        m_AppName = (char*)"New Open GL App";
        m_ScreenWidth = 80;
        m_ScreenHeight = 30;
    }

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
    void Start()
    {
        OnStart();
        OnLogWarning("App Started.");

        while (!glfwWindowShouldClose(m_Window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            OnUpdate((float)glfwGetTime());

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }

        OnTerminate();
        OnLogWarning("App Terminated.");

        glfwTerminate();
    }

    ~LTRAppEmbedderGL()
    {
    }
private:
    void handle_resize()
    {
        glViewport(0, 0, m_ScreenWidth, m_ScreenHeight);            // reset the viewport
        glMatrixMode(GL_PROJECTION);                                // modify the projection matrix
        glLoadIdentity();                                           // load an identity matrix into the projection matrix
        glOrtho(0, m_ScreenWidth, 0, m_ScreenHeight, -1.0, 1.0);    // create new projection matrix

        /// Important!!! You need to switch back to the model-view matrix
        /// or else your OpenGL calls are modifying the projection matrix!
        glMatrixMode(GL_MODELVIEW); // return to the model matrix
        glLoadIdentity();           // load an identity matrix into the model-view matrix
    }
protected:
    virtual void OnStart()=0;
    virtual void OnUpdate(float deltaTime)=0;
    virtual void OnTerminate(){};

    virtual void OnLogWarning(const char* msg) = 0;
    virtual void OnLogError(int err, const char* msg) = 0;
protected:
    GLFWwindow* m_Window;
public:
    char* m_AppName;
    int m_ScreenWidth;
    int m_ScreenHeight;
};