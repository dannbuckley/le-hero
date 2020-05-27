/**
 * Renderer.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "Renderer.h"
#include "Timer.h"
#include "spdlog/spdlog.h"

namespace le_hero {
    namespace graphics {
        SDL_Surface* Renderer::load_surface(const char* path)
        {
            PROFILE_GRAPHICS_TIMER();

            // attempt to load image file
            SDL_Surface* file_surface = IMG_Load(path);
            if (file_surface == NULL) {
                spdlog::get("graphics_logger")->error("Could not load image. SDL_image Error: {}", IMG_GetError());
                return NULL;
            }

            return file_surface;
        }

        bool Renderer::initialize_gl()
        {
            PROFILE_GRAPHICS_TIMER();

            glClear(GL_COLOR_BUFFER_BIT);
            glViewport(0.0f, 0.0f, this->width, this->height);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glOrtho(0.0, this->width, this->height, 0.0, 1.0, -1.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glClearColor(0.0f, 0.0f, 0.0, 1.0f);

            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            return true;
        }

        void Renderer::apply_png()
        {
            PROFILE_GRAPHICS_TIMER();

            glGenTextures(1, &txID);
            glBindTexture(GL_TEXTURE_2D, txID);

            // set color mode based on PNG data
            int mode = GL_RGB;
            switch (this->game_png_surface->format->BytesPerPixel) {
            case 1:
                mode = GL_LUMINANCE;
                break;
            case 2:
                mode = GL_LUMINANCE_ALPHA;
                break;
            case 3:
                break;
            case 4:
                mode = GL_RGBA;
                break;
            }

            // apply PNG texture
            glTexImage2D(GL_TEXTURE_2D, 0, mode, this->game_png_surface->w, this->game_png_surface->h, 0, mode, GL_UNSIGNED_BYTE, this->game_png_surface->pixels);

            auto error = glGetError();
            if (error != GL_NO_ERROR) {
                spdlog::get("graphics_logger")->error("Error in OpenGL, {}", glewGetErrorString(error));
            }

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            // unbind texture
            glBindTexture(GL_TEXTURE_2D, NULL);
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
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
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

            // load and apply 640x480 test image
            this->load_image();
            this->apply_png();
            return true;
        }

        bool Renderer::load_image()
        {
            PROFILE_GRAPHICS_TIMER();

            // load PNG as SDL surface
            this->game_png_surface = this->load_surface("img/TempLoadingScreen.png");

            if (this->game_png_surface == NULL) {
                spdlog::get("graphics_logger")->error("Could not load PNG image.");
                return false;
            }

            return true;
        }

        void Renderer::render()
        {
            // render PNG image to game window
            glClear(GL_COLOR_BUFFER_BIT);

            glLoadIdentity();
            glBindTexture(GL_TEXTURE_2D, this->txID);

            glBegin(GL_QUADS);
            glTexCoord2f(0.f, 0.f); glVertex2f(0.f, 0.f);
            glTexCoord2f(1.f, 0.f); glVertex2f(this->width, 0.f);
            glTexCoord2f(1.f, 1.f); glVertex2f(this->width, this->height);
            glTexCoord2f(0.f, 1.f); glVertex2f(0.f, this->height);
            glEnd();

            SDL_GL_SwapWindow(this->game_window);
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
    }
}