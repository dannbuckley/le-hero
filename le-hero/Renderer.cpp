/**
 * Renderer.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "Renderer.h"
#include "Timer.h"
#include "spdlog/spdlog.h"

namespace le_hero {
    namespace graphics {
        bool Renderer::initialize_gl()
        {
            PROFILE_GRAPHICS_TIMER();

            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            GLCall(glViewport(0.0f, 0.0f, this->width, this->height));

            GLCall(glClearColor(0.0f, 0.0f, 0.0, 1.0f));

            GLCall(glEnable(GL_BLEND));
            GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
            return true;
        }

        graphics::Renderer::Renderer(int w, int h) : width(w), height(h)
        {
            this->initialized = this->start_window();
        }

        bool Renderer::is_initialized()
        {
            return this->initialized;
        }

        bool Renderer::start_window()
        {
            PROFILE_GRAPHICS_TIMER();

            // initialize SDL video
            if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                spdlog::get("graphics_logger")->error("Could not initialize SDL. SDL Error: {}", SDL_GetError());
                return false;
            }

            spdlog::get("graphics_logger")->info("SDL initialized successfully.");

            // create game window
            this->game_window = SDL_CreateWindow("le-hero",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                this->width,
                this->height,
                SDL_WINDOW_OPENGL);

            if (this->game_window == NULL) {
                spdlog::get("graphics_logger")->error("Could not create window. SDL Error: {}", SDL_GetError());
                return false;
            }

            spdlog::get("graphics_logger")->info("Game window created successfully.");

            // initialize PNG
            if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                spdlog::get("graphics_logger")->error("Could not initialize SDL_image. SDL_image Error: {}", IMG_GetError());
                return false;
            }

            spdlog::get("graphics_logger")->info("SDL_image library initialized successfully.");

            // store game window surface
            this->game_screen_surface = SDL_GetWindowSurface(this->game_window);

            // set OpenGL version to 3.1
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // create context for OpenGL using SDL
            this->gl_context = SDL_GL_CreateContext(this->game_window);
            if (gl_context == NULL) {
                spdlog::get("graphics_logger")->error("Could not create OpenGL context. SDL Error: {}", SDL_GetError());
                return false;
            }

            // initialize GLEW
            glewExperimental = true;
            auto glew_error = glewInit();
            if (glew_error != GLEW_OK) {
                spdlog::get("graphics_logger")->error("Could not initialize GLEW. {}", glewGetErrorString(glew_error));
                return false;
            }

            // enable VSync
            if (SDL_GL_SetSwapInterval(1) < 0) {
                spdlog::get("graphics_logger")->error("Could not enable VSync. SDL Error: {}", SDL_GetError());
                return false;
            }

            this->initialize_gl();
            return true;
        }

        void Renderer::quit()
        {
            PROFILE_GRAPHICS_TIMER();

            // free PNG surface memory
            SDL_FreeSurface(this->game_png_surface);
            this->game_png_surface = NULL;

            // destroy game window
            SDL_DestroyWindow(this->game_window);
            this->game_window = NULL;

            // unload image library and clear SDL subsystems
            IMG_Quit();
            SDL_Quit();
        }

        void Renderer::clear() const
        {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
        }

        void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
        {
            shader.bind();
            va.bind();
            ib.bind();

            GLCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
        }

        void Renderer::swap_buffers()
        {
            SDL_GL_SwapWindow(this->game_window);
        }
    }
}