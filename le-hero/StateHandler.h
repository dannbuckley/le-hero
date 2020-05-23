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
            virtual bool enter_state(enum StateTypes new_state) = 0;
            virtual bool exit_current_state() = 0;

        public:
            virtual bool act(enum StateActions action) = 0;
            virtual enum StateTypes get_current_state() = 0;
            virtual ~StateHandler() {};

            static std::string get_state_string(enum StateTypes _state) {
                switch (_state) {
                case StateTypes::STATELESS:
                    return "STATELESS";
                case StateTypes::INITIALIZING:
                    return "INITIALIZING";
                case StateTypes::PARSING_SETTINGS:
                    return "PARSING_SETTINGS";
                case StateTypes::PARSING_QUESTS_INDEX:
                    return "PARSING_QUESTS_INDEX";
                default:
                    return "";
                }
            }

            static std::string get_action_string(enum StateActions _action) {
                switch (_action) {
                case StateActions::START_SETUP:
                    return "START_SETUP";
                case StateActions::FINISH_SETUP:
                    return "FINISH_SETUP";
                case StateActions::START_PARSING_SETTINGS:
                    return "START_PARSING_SETTINGS";
                case StateActions::FINISH_PARSING_SETTINGS:
                    return "FINISH_PARSING_SETTINGS";
                case StateActions::START_PARSING_QUESTS_INDEX:
                    return "START_PARSING_QUESTS_INDEX";
                case StateActions::FINISH_PARSING_QUESTS_INDEX:
                    return "FINISH_PARSING_QUESTS_INDEX";
                default:
                    return "";
                }
            }
        };
    }
}

