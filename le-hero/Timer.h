/**
 * Timer.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <chrono>
#include "spdlog/spdlog.h"

namespace le_hero {
#define PROFILING 1
#if PROFILING
#define PROFILE_TIMER() diagnostics::Timer t(__FUNCTION__)
	namespace diagnostics {
		class Timer
		{
		private:
			const char* name;
			std::chrono::steady_clock::time_point start;

			void stop() {
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> duration = end - start;

				float ms = duration.count() * 1000.0f;
				spdlog::get("logger")->debug("Process '{}' took {}ms", name, ms);
			}

		public:
			Timer(const char* name): name(name) {
				start = std::chrono::high_resolution_clock::now();
			}

			~Timer() {
				stop();
			}
		};
	}
#else
#define PROFILE_TIMER()
#endif
}