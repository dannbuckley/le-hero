/*
 * IndexBuffer.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "IndexBuffer.h"
#include "GLDebug.h"

namespace le_hero {
	namespace graphics {
		IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
			: count(count)
		{
			ASSERT(sizeof(unsigned int) == sizeof(GLuint));

			glGenBuffers(1, &renderer_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &renderer_id);
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}