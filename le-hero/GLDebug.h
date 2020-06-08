#pragma once

#include <GL\glew.h>
#include "spdlog/spdlog.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) gl_clear_error();	\
	x;								\
	ASSERT(gl_log_call(#x, __FILE__, __LINE__))

static void gl_clear_error() {
	while (glGetError() != GL_NO_ERROR);
}

static bool gl_log_call(const char* func, const char* file, unsigned int line) {
	while (GLenum error = glGetError()) {
		spdlog::get("graphics_logger")->error("[OpenGL Error] ({}): {} {}:{}", error, func, file, line);
		return false;
	}
	return true;
}