#pragma once

#include <string>
#include <SDL.h>

namespace le_hero {
	namespace graphics {
		class Texture
		{
		private:
			unsigned int renderer_id = 0;
			std::string filepath;
			unsigned char* local_buffer = nullptr;
			int width = 0, height = 0, bpp = 0;
			SDL_Surface* texture_surface = nullptr;

		public:
			Texture(const std::string& path);
			~Texture();

			void bind(unsigned int slot = 0) const;
			void unbind() const;

			inline int get_width() const {
				return width;
			}

			inline int get_height() const {
				return height;
			}
		};
	}
}