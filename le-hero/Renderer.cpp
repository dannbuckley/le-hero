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

            // convert image file surface to game window format
            auto image_surface = SDL_ConvertSurface(file_surface, this->game_screen_surface->format, 0);

            if (image_surface == NULL) {
                spdlog::get("graphics_logger")->error("Could not convert image surface from file '{}'. SDL Error: {}", path, SDL_GetError());
                return NULL;
            }

            // free image file surface memory
            SDL_FreeSurface(file_surface);

            return image_surface;
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
                SDL_WINDOW_SHOWN);

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

        void Renderer::apply_image()
        {
            // render PNG image to game window
            SDL_BlitSurface(this->game_png_surface, NULL, this->game_screen_surface, NULL);
            SDL_UpdateWindowSurface(this->game_window);
        }

        void Renderer::quit()
        {
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