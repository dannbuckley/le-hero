#include <iostream>
#include <fstream>
#include <sstream>

#include "GLDebug.h"
#include "Shader.h"

namespace le_hero {
	namespace graphics {
		ShaderProgramSource Shader::parse_shader(const std::string& filepath)
		{
			std::ifstream stream(filepath);

			enum class ShaderType {
				NONE = -1,
				VERTEX = 0,
				FRAGMENT = 1
			};

			std::string line;
			std::stringstream ss[2];
			ShaderType type = ShaderType::NONE;
			
			while (getline(stream, line)) {
				if (line.find("#shader") != std::string::npos) {
					if (line.find("vertex") != std::string::npos) {
						type = ShaderType::VERTEX;
					}
					else if (line.find("fragment") != std::string::npos) {
						type = ShaderType::FRAGMENT;
					}
				}
				else {
					ss[(unsigned int)type] << line << std::endl;
				}
			}

			return { ss[0].str(), ss[1].str() };
		}

		unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
		{
			GLCall(unsigned int id = glCreateShader(type));
			const char* src = source.c_str();
			GLCall(glShaderSource(id, 1, &src, nullptr));
			GLCall(glCompileShader(id));

			int result;
			GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
			if (result == GL_FALSE) {
				int length;
				GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

				char* message = (char*)_malloca(length * sizeof(char));
				GLCall(glGetShaderInfoLog(id, length, &length, message));

				spdlog::get("graphics_logger")->error("Failed to compile {} shader!", type);
				spdlog::get("graphics_logger")->error("Message: {}", message);

				GLCall(glDeleteShader(id));
				return 0;
			}

			return id;
		}

		unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
		{
			GLCall(unsigned int program = glCreateProgram());
			unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
			unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

			GLCall(glAttachShader(program, vs));
			GLCall(glAttachShader(program, fs));
			GLCall(glLinkProgram(program));
			GLCall(glValidateProgram(program));

			GLCall(glDeleteShader(vs));
			GLCall(glDeleteShader(fs));

			return program;
		}

		int Shader::get_uniform_location(const std::string& name)
		{
			if (uniform_cache.find(name) != uniform_cache.end()) {
				return uniform_cache[name];
			}

			GLCall(int location = glGetUniformLocation(renderer_id, name.c_str()));
			if (location == -1) {
				spdlog::get("graphics_logger")->warn("Uniform {} doesn't exist!", name);
			}

			uniform_cache[name] = location;
			return location;
		}

		Shader::Shader(const std::string& filepath)
			: filepath(filepath)
		{
			ShaderProgramSource source = parse_shader(filepath);
			renderer_id = create_shader(source.vertex_source, source.fragment_source);
		}

		Shader::~Shader()
		{
			GLCall(glDeleteProgram(renderer_id));
		}

		void Shader::bind() const
		{
			GLCall(glUseProgram(renderer_id));
		}

		void Shader::unbind() const
		{
			GLCall(glUseProgram(0));
		}

		void Shader::set_uniform_1i(const std::string& name, int value)
		{
			GLCall(glUniform1i(get_uniform_location(name), value));
		}

		void Shader::set_uniform_1f(const std::string& name, float value)
		{
			GLCall(glUniform1f(get_uniform_location(name), value));
		}

		void Shader::set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3)
		{
			GLCall(glUniform4f(get_uniform_location(name), v0, v1, v2, v3));
		}

		void Shader::set_uniform_mat_4f(const std::string& name, const glm::mat4& matrix)
		{
			GLCall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]));
		}
	}
}