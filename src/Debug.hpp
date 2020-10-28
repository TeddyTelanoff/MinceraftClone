#pragma once

#include <iostream>
#include <GL/glew.h>

#define cout(msg) std::cout << "[$]<" << __FILE__ << ":" << __LINE__ << "> " << msg << std::endl
#define cerr(msg) std::cerr << "[!]<" << __FILE__ << ":" << __LINE__ << "> " << msg << std::endl

#if _DEBUG
#define dout(msg) std::cout << "[$]<" << __FILE__ << ":" << __LINE__ << "> " << msg << std::endl
#define derr(msg) std::cerr << "[!]<" << __FILE__ << ":" << __LINE__ << "> " << msg << std::endl
#define dif(c, code) if (c) { code }
#define drun(code) code
#define rrun(code)

#define asrc(c) dif(!(c), __debugbreak();)
#define asr(c, msg) dif(!(c), cerr(msg); __debugbreak(); )

#define gldebug(call) GLClearError(); call; if (!GLLogCall(#call, __FILE__, __LINE__)) __debugbreak()

static char const* gl_error_string(GLenum const err) noexcept
{
    switch (err)
    {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";

    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";

    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";

    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";

    case GL_TABLE_TOO_LARGE:
        return "GL_TABLE_TOO_LARGE";

    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";

    default:
        return nullptr;
    }
}

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        derr("[OpenGL Error] (" << gl_error_string(error) << "): " << function << " " << file << ":" << line);
        return false;
    }
    return true;
}
#else
#define dout(x)
#define derr(x)
#define dif(c, code)
#define drun(code)
#define rrun(code) code

#pragma warning( disable : 5 )
#define asrc(c)
#define asr(c, msg)
#pragma warning( default : 5 )

#define gldebug(call) call
#endif