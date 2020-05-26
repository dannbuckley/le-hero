/**
 * Renderer.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "SDLIncludes.h"

namespace le_hero {
    namespace graphics {
        class Renderer
        {
        private:
            int width = 0, height = 0;
            bool initialized = false;
            SDL_Window* game_window = NULL;
            SDL_Surface* game_screen_surface = NULL;
            SDL_Surface* game_png_surface = NULL;

            SDL_Surface* load_surface(const char* path);

        public:
            Renderer(int w = 640, int h = 480);

            bool is_initialized();

            bool start_window();
            bool load_image();
            void apply_image();
            void quit();
        };
    }
}