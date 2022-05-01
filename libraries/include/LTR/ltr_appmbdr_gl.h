#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* Lother App Embedder for Open GL */
class app_embedder_gl
{
public:
    app_embedder_gl()
    {
        m_window = NULL;

        m_AppName = (char*)"New Open GL App";
        m_ScreenWidth = 80;
        m_ScreenHeight = 30;
    }

    int ConstructApp(int width, int height)
    {
        m_ScreenWidth = width;
        m_ScreenHeight = height;

        // Generate window
        if (!glfwInit())
        {
            HandleError(-1, "GLFW could not init.");
            return -1;
        }

        m_window = glfwCreateWindow(m_ScreenWidth, m_ScreenHeight, m_AppName, NULL, NULL);
        if (!m_window)
        {
            glfwTerminate();
            HandleError(-1, "GLFW could not create window.");
            return -1;
        }

        glfwMakeContextCurrent(m_window);

        /* Init glew*/
        if (glewInit() != GLEW_OK)
        {
            HandleError(-1, "GLEW could not init.");
            return -1;
        }

        return 0;
    }

    void Start()
    {
        OnStart();
        HandleWarning("App Started.");
        
        while (!glfwWindowShouldClose(m_window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(m_window);

            OnUpdate((float)glfwGetTime());

            glfwPollEvents();
        }

        OnTerminate();
        HandleWarning("App Terminated.");

        glfwTerminate();
    }

    int ScreenWidth()
    {
        return m_ScreenWidth;
    }

    int ScreenHeight()
    {
        return m_ScreenWidth;
    }

    ~app_embedder_gl()
    {
    }
protected:
    virtual void OnStart()=0;
    virtual void OnUpdate(float deltaTime)=0;
    virtual void OnTerminate(){};

    virtual void HandleWarning(const char* msg) = 0;
    virtual void HandleError(int err, const char* msg) = 0;
protected:
    GLFWwindow* m_window;
public:
    char* m_AppName;
    int m_ScreenWidth;
    int m_ScreenHeight;
};