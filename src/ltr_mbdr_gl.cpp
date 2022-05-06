#include <LTR/ltr_mbdr_gl.h>

#pragma region App Base

LTR_Embedder::LTR_Embedder()
{
    // Initialize default values
    m_Window = NULL;

    m_AppName = (char*)"New Open GL App";
    m_ScreenWidth = 80;
    m_ScreenHeight = 30;

    m_shader = 0;
}

int LTR_Embedder::ConstructApp()
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

void LTR_Embedder::Run()
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

LTR_Embedder::~LTR_Embedder()
{
}

#pragma endregion

void LTR_Embedder::AppStart()
{
    float positions[6] = { -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

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

    OnLogWarning("Shader Compilation done.");
}

void LTR_Embedder::AppFrameUpdate()
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

unsigned int LTR_Embedder::CompileShader(unsigned int type, const std::string& source)
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

        OnLogError(0, msg);
        delete[]msg;

        glDeleteShader(id);
        return 0;
    }

    return id;
}
unsigned int LTR_Embedder::CreateShader(const std::string& sVertex, const std::string& sFragment)
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

#pragma region Class Static Methods

#pragma endregion