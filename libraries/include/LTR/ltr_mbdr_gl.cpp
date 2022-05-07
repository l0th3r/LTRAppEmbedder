#include "ltr_mbdr_gl.h"

using namespace ltr;

#pragma region App Base

AppEmbedder::AppEmbedder()
{
    // Initialize default values
    m_Window = NULL;

    m_AppName = (char*)"New Open GL App";
    m_ScreenWidth = 80;
    m_ScreenHeight = 30;

    m_shader = 0;
}

int AppEmbedder::ConstructApp()
{
    // Generate window
    if (!glfwInit())
    {
        ThrowError(ErrContext::GLFW, ErrCode::init);
        return -1;
    }

    m_Window = glfwCreateWindow(m_ScreenWidth, m_ScreenHeight, m_AppName, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        ThrowError(ErrContext::GLFW, ErrCode::creating_window);
        return -1;
    }

    // Make the window the current context
    glfwMakeContextCurrent(m_Window);

    // Init glew
    if (glewInit() != GLEW_OK)
    {
        ThrowError(ErrContext::GLEW, ErrCode::init);
        return -1;
    }

    return 0;
}

void AppEmbedder::Run()
{
    // Focal app start
    AppStart();

    // Call user start
    OnStart();
    ThrowWarning(ErrContext::App, ErrCode::init);

    // Frame update
    while (!glfwWindowShouldClose(m_Window))
    {
        // Local frame update
        AppFrameUpdate();
    }

    OnTerminate();
    ThrowWarning(ErrContext::App, ErrCode::terminate);

    glfwTerminate();
}

void AppEmbedder::ThrowLog(const std::string message)
{
    OnLog(message);
}
void AppEmbedder::ThrowWarning(ErrContext context, ErrCode warning)
{
    OnLogWarning(ErrContextToStr(context), ErrCodeToStr(warning));
    OnRawWarning(context, warning);
}
void AppEmbedder::ThrowError(ErrContext context, ErrCode warning)
{
    OnLogError(ErrContextToStr(context), ErrCodeToStr(warning));
    OnRawError(context, warning);
}

AppEmbedder::~AppEmbedder()
{
}

#pragma endregion

#pragma region App Runtime
void AppEmbedder::AppStart()
{
    float positions[6] = { -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    ThrowWarning(ErrContext::Shader, ErrCode::shader_compilation_start);

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    ThrowWarning(ErrContext::Shader, ErrCode::shader_compilation_done);
}

void AppEmbedder::AppFrameUpdate()
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

// Shaders
unsigned int AppEmbedder::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = new char[length];
        glGetShaderInfoLog(id, length, &length, msg);

        ThrowError(ErrContext::Shader, ErrCode::shader_compilation);
        ThrowLog(msg);

        delete[]msg;

        glDeleteShader(id);
        return 0;
    }

    return id;
}
unsigned int AppEmbedder::CreateShader(const std::string& sVertex, const std::string& sFragment)
{
    unsigned int program = glCreateProgram();
    unsigned int sv = CompileShader(GL_VERTEX_SHADER, sVertex);
    unsigned int sf = CompileShader(GL_FRAGMENT_SHADER, sFragment);

    glAttachShader(program, sv);
    glAttachShader(program, sf);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(sv);
    glDeleteShader(sf);

    return program;
}

#pragma endregion

#pragma region Class Static Methods

#pragma endregion