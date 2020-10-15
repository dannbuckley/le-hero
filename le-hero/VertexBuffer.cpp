/*
 * VertexBuffer.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "GLDebug.h"
#include "VertexBuffer.h"

namespace le_hero {
	namespace graphics {
		VertexBuffer::VertexBuffer(const void* data, unsigned int size)
		{
			glGenBuffers(1, &renderer_id);
			glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &renderer_id);
		}

		void VertexBuffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
		}

		void VertexBuffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}