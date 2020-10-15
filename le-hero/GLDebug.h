/*
 * GLDebug.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <GL\glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();