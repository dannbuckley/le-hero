/*
 * VertexArray.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "VertexArray.h"

namespace le_hero {
	namespace graphics {
		VertexArray::VertexArray()
		{
			GLCall(glGenVertexArrays(1, &renderer_id));
		}

		VertexArray::~VertexArray()
		{
			GLCall(glDeleteVertexArrays(1, &renderer_id));
		}

		void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
		{
			bind();
			vb.bind();

			const auto& elements = layout.get_elements();
			unsigned int offset = 0;
			for (unsigned int i = 0; i < elements.size(); i++) {
				const auto& element = elements[i];
				GLCall(glEnableVertexAttribArray(i));
				GLCall(glVertexAttribPointer(i, element.count, element.type,
					element.normalized, layout.get_stride(), (const void*)offset));
				offset += element.count * VertexBufferElement::get_size_of_type(element.type);
			}
		}

		void VertexArray::bind() const
		{
			GLCall(glBindVertexArray(renderer_id));
		}

		void VertexArray::unbind() const
		{
			GLCall(glBindVertexArray(0));
		}
	}
}