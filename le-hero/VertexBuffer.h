#pragma once

namespace le_hero {
	namespace graphics {
		class VertexBuffer
		{
		private:
			unsigned int renderer_id;

		public:
			VertexBuffer(const void* data, unsigned int size);
			~VertexBuffer();

			void bind() const;
			void unbind() const;
		};
	}
}