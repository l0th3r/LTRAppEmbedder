#pragma once

#include "ltr_err.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

namespace ltr
{
    class AppEmbedder
    {
#pragma region App Base
    public:
        AppEmbedder();
        ~AppEmbedder();

        // Create window and setup GLFW and GLEW
        int ConstructApp();

        // App Runtime Execution
        void Run();

        #pragma endregion

#pragma region App Runtime
    private:
        void AppStart();
        void AppFrameUpdate();

        void ThrowLog(const std::string message);
        void ThrowWarning(ErrContext context, ErrCode warning, const std::string log);
        void ThrowWarning(ErrContext context, ErrCode warning);
        void ThrowError(ErrContext context, ErrCode warning, const std::string log);
        void ThrowError(ErrContext context, ErrCode warning);

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
        virtual void OnLog(const std::string log) {};
        virtual void OnLogWarning(const std::string, const std::string) {};
        virtual void OnRawWarning(ErrContext context, ErrCode warning) {};
        virtual void OnLogError(const std::string, const std::string) {};
        virtual void OnRawError(ErrContext context, ErrCode error) {};
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
}