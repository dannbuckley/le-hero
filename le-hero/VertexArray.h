/*
 * VertexArray.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace le_hero {
	namespace graphics {
		class VertexArray
		{
		private:
			unsigned int renderer_id;

		public:
			VertexArray();
			~VertexArray();

			void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

			void bind() const;
			void unbind() const;
		};
	}
}