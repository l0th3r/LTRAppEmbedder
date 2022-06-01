#pragma once

#include <iostream>
#include <string>

namespace ltr
{
    /// <summary>
    /// Define the context of an error or warning.
    /// </summary>
    enum class ErrContext : int
    {
        App = 1,
        GLFW = 10,
        GLEW = 20,
        Shader = 30,
        GL = 40
    };

    /// <summary>
    /// Define the specific error or warning
    /// </summary>
    enum class ErrCode : int
    {
        no_err = 0,
        init = 1,
        terminate = 2,

        creating_window = 101,

        shader_parsing = 301,
        shader_compilation = 302,

        draw = 401
    };

    const std::string ErrContextToStr(const ErrContext context);
    const std::string ErrCodeToStr(const ErrCode code);
}