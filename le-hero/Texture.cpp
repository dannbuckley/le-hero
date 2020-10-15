/*
 * Texture.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <SDL_image.h>
#include "GLDebug.h"
#include "Texture.h"

namespace le_hero {
	namespace graphics {
		Texture::Texture(const std::string& path) : filepath(path)
		{
			texture_surface = IMG_Load(path.c_str());
			local_buffer = (unsigned char*)texture_surface->pixels;
			bpp = texture_surface->format->BytesPerPixel;
			width = texture_surface->w;
			height = texture_surface->h;

			glGenTextures(1, &renderer_id);
			glBindTexture(GL_TEXTURE_2D, renderer_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, local_buffer);
			glBindTexture(GL_TEXTURE_2D, 0);

			if (local_buffer) {
				SDL_FreeSurface(texture_surface);
				local_buffer = nullptr;
			}
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &renderer_id);
		}

		void Texture::bind(unsigned int slot) const
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, renderer_id);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}