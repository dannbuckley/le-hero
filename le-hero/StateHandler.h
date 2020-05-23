/**
 * StateHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <cstdint>

namespace le_hero {
    namespace state {
        enum class StateTypes : uint8_t {
            STATELESS = 0,
            INITIALIZING,
        };

        enum class StateActions : uint8_t {
            START_SETUP = 0,
            FINISH_SETUP,
        };

        class StateHandler
        {
        protected:
            virtual bool exit_current_state() = 0;

        public:
            virtual bool act(enum StateActions action) = 0;
            virtual enum StateTypes get_current_state() = 0;
            virtual ~StateHandler() {};
        };
    }
}

