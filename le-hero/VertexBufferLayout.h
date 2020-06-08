#pragma once

#include <vector>
#include "GLDebug.h"

namespace le_hero {
	namespace graphics {
		struct VertexBufferElement {
			unsigned int type;
			unsigned int count;
			unsigned char normalized;

			static unsigned int get_size_of_type(unsigned int type) {
				switch (type) {
				case GL_FLOAT:			return 4;
				case GL_UNSIGNED_INT:	return 4;
				case GL_UNSIGNED_BYTE:	return 1;
				}
				ASSERT(false);
				return 0;
			}
		};

		class VertexBufferLayout {
		private:
			std::vector<VertexBufferElement> buffer_elements;
			unsigned int stride;
			
		public:
			VertexBufferLayout()
				: stride(0) {}

			template<typename T>
			void push(unsigned int count) {
				static_assert(false);
			}

			template<>
			void push<float>(unsigned int count) {
				buffer_elements.push_back({ GL_FLOAT, count, GL_FALSE });
				stride += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
			}

			template<>
			void push<unsigned int>(unsigned int count) {
				buffer_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
				stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
			}

			template<>
			void push<unsigned char>(unsigned int count) {
				buffer_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
				stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
			}

			inline const std::vector<VertexBufferElement> get_elements() const {
				return buffer_elements;
			}

			inline const unsigned int get_stride() const {
				return stride;
			}
		};
	}
}