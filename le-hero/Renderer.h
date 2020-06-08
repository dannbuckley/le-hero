/**
 * Renderer.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "GraphicsIncludes.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

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
            SDL_GLContext gl_context = NULL;
            GLuint txID = 0;

            bool initialize_gl();

        public:
            Renderer(int w = 640, int h = 480);

            bool is_initialized();

            bool start_window();
            void quit();

            void clear() const;
            void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
            void swap_buffers();
        };
    }
}