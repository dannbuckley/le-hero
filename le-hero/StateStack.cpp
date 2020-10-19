/*
* StateStack.cpp
* Copyright (c) 2020 Daniel Buckley
*/

#include "StateStack.h"

namespace le_hero {
	namespace state {
		bool StateStack::is_empty()
		{
			return this->states->size() == 0;
		}

		StateTypes StateStack::peek()
		{
			return this->states->back();
		}

		void StateStack::push(StateTypes state)
		{
			this->states->push_back(state);
		}

		void StateStack::pop()
		{
			if (!this->is_empty()) {
				this->states->pop_back();
			}
		}

		std::vector<std::string> StateStack::get_display_vector()
		{
			if (this->is_empty()) {
				return std::vector<std::string>();
			}

			std::vector<std::string> display_names;
			display_names.reserve(this->states->size());
			for (auto i = this->states->begin(); i < this->states->end(); i++) {
				display_names.push_back(get_state_string(*i));
			}
			return display_names;
		}
	}
}
