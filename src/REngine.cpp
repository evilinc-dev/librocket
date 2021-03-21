#include <REngine.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>

namespace rocket
{

    REngine::REngine() {}

    REngine::~REngine() {}

    API REngine& REngine::instance() {
        static REngine instance;
        return instance;
    }

    API void REngine::init() {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        this->window = SDL_CreateWindow(
            "librocket",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1920,
            1080,
            SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS
        );

        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo((SDL_Window*)this->window, &wmi)) {
            throw std::exception("WMI FAILURE");
        }

        this->context = SDL_GL_CreateContext((SDL_Window*)this->window);

    }

    API void REngine::setClearColor(const RVector3& color) {
        glClearColor(color.x, color.y, color.z, 1.0f);
    }

    API void REngine::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    API void REngine::present() {
        SDL_GL_SwapWindow((SDL_Window*)this->window);
        SDL_Delay(1);
    }

    API void REngine::shutdown() {

        SDL_GL_DeleteContext((SDL_GLContext*)this->context);
        SDL_DestroyWindow((SDL_Window*)this->window);
        SDL_Quit();
    }

}