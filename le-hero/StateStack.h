/*
 * StateStack.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <memory>
#include <vector>
#include "StateHandler.h"

namespace le_hero {
	namespace state {
		class StateStack
		{
		public:
			StateStack() {
				states = std::make_unique<std::vector<StateTypes>>();
			}
			virtual ~StateStack() {}

			bool is_empty();
			StateTypes peek();
			void push(StateTypes state);
			void pop();

			// debug method for viewing states in stack
			std::vector<std::string> get_display_vector();

		private:
			std::unique_ptr<std::vector<StateTypes>> states;
		};
	}
}