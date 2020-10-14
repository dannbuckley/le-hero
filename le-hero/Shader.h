/*
 * Shader.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <string>
#include <unordered_map>
#include <glm.hpp>

namespace le_hero {
	namespace graphics {
		struct ShaderProgramSource {
			std::string vertex_source;
			std::string fragment_source;
		};

		class Shader
		{
		private:
			std::string filepath;
			unsigned int renderer_id = 0;
			std::unordered_map<std::string, int> uniform_cache;

			ShaderProgramSource parse_shader(const std::string& filepath);
			unsigned int compile_shader(unsigned int type, const std::string& source);
			unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);
			int get_uniform_location(const std::string& name);

		public:
			Shader(const std::string& filepath);
			~Shader();

			void bind() const;
			void unbind() const;

			/* Set Uniforms */

			void set_uniform_1i(const std::string& name, int value);
			void set_uniform_1f(const std::string& name, float value);
			void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3);
			void set_uniform_mat_4f(const std::string& name, const glm::mat4& matrix);
		};
	}
}