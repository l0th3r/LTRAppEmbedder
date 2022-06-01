#include "ltr_mbdr_gl.h"

#include "ltr_file.h"

using namespace ltr;

#pragma region App Base

AppEmbedder::AppEmbedder()
{
    // Initialize default values
    m_Window = NULL;

    m_AppName = (char*)"New Open GL App";
    m_ScreenWidth = 80;
    m_ScreenHeight = 30;

    m_shader_vertex_path = "E:/Projects/LTRAppEmbedder/src/shaders/vertex.shader";
    m_shader_fragment_path = "E:/Projects/LTRAppEmbedder/src/shaders/fragment.shader";

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
    ThrowWarning(ErrContext::App, ErrCode::init, "(app started)");

    // Frame update
    while (!glfwWindowShouldClose(m_Window))
    {
        // Local frame update
        AppFrameUpdate();
    }

    OnTerminate();
    ThrowWarning(ErrContext::App, ErrCode::terminate, "(app terminated)");

    glfwTerminate();
}

#pragma region App Logs
void AppEmbedder::ThrowLog(const std::string message, bool newLine)
{
    if (newLine)
        OnLog('\n' + message);
    else
        OnLog(message);
}
void AppEmbedder::ThrowWarning(ErrContext context, ErrCode warning)
{
    OnLogWarning(ErrContextToStr(context), ErrCodeToStr(warning));
    OnRawWarning(context, warning);
}
void AppEmbedder::ThrowWarning(ErrContext context, ErrCode warning, const std::string log)
{
    OnLogWarning(ErrContextToStr(context), ErrCodeToStr(warning));
    OnRawWarning(context, warning);
    ThrowLog(log, false);
}
void AppEmbedder::ThrowError(ErrContext context, ErrCode warning)
{
    OnLogError(ErrContextToStr(context), ErrCodeToStr(warning));
    OnRawError(context, warning);
}
void AppEmbedder::ThrowError(ErrContext context, ErrCode warning, const std::string log)
{
    OnLogError(ErrContextToStr(context), ErrCodeToStr(warning));
    OnRawError(context, warning);
    ThrowLog(log, false);
}
#pragma endregion

AppEmbedder::~AppEmbedder()
{
}

#pragma endregion

#pragma region App Runtime
void AppEmbedder::AppStart()
{
    float positions[] =
    {
        -0.5f, -0.5f,   // 0
        0.5f, -0.5f,    // 1
        0.5f, 0.5f,     // 2
        -0.5f, 0.5f,    // 3
    };

    unsigned int indices[] =
    {
        0, 1, 2, // first triangle
        2, 3, 0  // second triangle
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ThrowWarning(ErrContext::Shader, ErrCode::shader_compilation, "started");

    CompileShaders();
}

void AppEmbedder::AppFrameUpdate()
{
    // Clear buffer
    glClear(GL_COLOR_BUFFER_BIT);
   
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    // Call user update
    OnUpdate((float)glfwGetTime());

    // Swap Buffers
    glfwSwapBuffers(m_Window);
    // Poll for and process events
    glfwPollEvents();
}

// Shaders
void AppEmbedder::CompileShaders()
{
    File vtx(m_shader_vertex_path.c_str()), fgmt(m_shader_fragment_path.c_str());

    unsigned int shader = CreateShader(vtx.content, fgmt.content);
    glUseProgram(shader);

    ThrowWarning(ErrContext::Shader, ErrCode::shader_compilation, "done");
}

unsigned int AppEmbedder::ParseShader(unsigned int type, const std::string& source)
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
    unsigned int sv = ParseShader(GL_VERTEX_SHADER, sVertex);
    unsigned int sf = ParseShader(GL_FRAGMENT_SHADER, sFragment);

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