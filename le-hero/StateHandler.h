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
            PARSING_SETTINGS,
            PARSING_QUESTS_INDEX,
        };

        enum class StateActions : uint8_t {
            START_SETUP = 0,
            FINISH_SETUP,
            START_PARSING_SETTINGS,
            FINISH_PARSING_SETTINGS,
            START_PARSING_QUESTS_INDEX,
            FINISH_PARSING_QUESTS_INDEX,
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

