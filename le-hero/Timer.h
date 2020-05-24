/**
 * Timer.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <chrono>
#include "spdlog/spdlog.h"

namespace le_hero {
	namespace diagnostics {
		class Timer
		{
		private:
			std::chrono::steady_clock::time_point start, end;
			std::chrono::duration<float> duration = std::chrono::duration<float>::min();

		public:
			Timer() {
				start = std::chrono::high_resolution_clock::now();
			}

			~Timer() {
				end = std::chrono::high_resolution_clock::now();
				duration = end - start;

				float ms = duration.count() * 1000.0f;
				spdlog::get("logger")->debug("Elapsed time: {}ms", ms);
			}
		};
	}
}