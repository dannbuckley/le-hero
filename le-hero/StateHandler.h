/**
 * StateHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <cstdint>

namespace le_hero {
    namespace state {
        enum class StateTypes : uint8_t {
            /* State stack is empty */
            STATELESS = 0,

            /* Initialization mode state */
            INITIALIZING,

            /* Parsing mode states */
            PARSING_SETTINGS,
            PARSING_QUESTS_INDEX,
            PARSING_QUEST_FILE,

            /* Quest mode states */
            EMBARKING_ON_QUEST,
            QUEST_AWAITING_ACTIONS,
            QUEST_READY_FOR_TURN,
            QUEST_PERFORMING_ACTIONS,

            /* Menu mode states */
            MAIN_MENU,
            MAIN_PLAY_SUBMENU,
            MAIN_PLAY_NEWSAVE_WARNING,
            MAIN_SETTINGS_SUBMENU,
        };

        enum class StateActions : uint8_t {
            /* Initialization mode actions */
            START_SETUP = 0,
            FINISH_SETUP,

            /* Parsing mode actions */
            START_PARSING_SETTINGS,
            FINISH_PARSING_SETTINGS,
            START_PARSING_QUESTS_INDEX,
            FINISH_PARSING_QUESTS_INDEX,
            START_PARSING_QUEST_FILE,
            FINISH_PARSING_QUEST_FILE,

            /* Quest mode actions */
            START_QUEST,
            END_QUEST,
            QUEST_START_TURN,
            QUEST_DECIDE_ACTIONS,
            QUEST_START_PERFORM_ACTIONS,
            QUEST_FINISH_PERFORM_ACTIONS,

            /* Menu mode actions */
            OPEN_MAIN_MENU,
            CLOSE_MAIN_MENU,
            OPEN_PLAY_SUBMENU,
            CLOSE_PLAY_SUBMENU,
            WARN_NEWSAVE_PLAY_SUBMENU,
            CLOSE_WARN_NEWSAVE_PLAY_SUBMENU,
            OPEN_SETTINGS_SUBMENU,
            CLOSE_SETTINGS_SUBMENU,
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
                    /* State stack is empty */
                case StateTypes::STATELESS:
                    return "STATELESS";

                    /* Initialization mode state */
                case StateTypes::INITIALIZING:
                    return "INITIALIZING";

                    /* Parsing mode states */
                case StateTypes::PARSING_SETTINGS:
                    return "PARSING_SETTINGS";
                case StateTypes::PARSING_QUESTS_INDEX:
                    return "PARSING_QUESTS_INDEX";
                case StateTypes::PARSING_QUEST_FILE:
                    return "PARSING_QUEST_FILE";

                    /* Quest mode states */
                case StateTypes::EMBARKING_ON_QUEST:
                    return "EMBARKING_ON_QUEST";
                case StateTypes::QUEST_AWAITING_ACTIONS:
                    return "QUEST_AWAITING_ACTIONS";
                case StateTypes::QUEST_READY_FOR_TURN:
                    return "QUEST_READY_FOR_TURN";
                case StateTypes::QUEST_PERFORMING_ACTIONS:
                    return "QUEST_PERFORMING_ACTIONS";

                    /* Menu mode states */
                case StateTypes::MAIN_MENU:
                    return "MAIN_MENU";
                case StateTypes::MAIN_PLAY_SUBMENU:
                    return "MAIN_PLAY_SUBMENU";
                case StateTypes::MAIN_PLAY_NEWSAVE_WARNING:
                    return "MAIN_PLAY_NEWSAVE_SUBMENU";
                case StateTypes::MAIN_SETTINGS_SUBMENU:
                    return "MAIN_SETTINGS_SUBMENU";
                default:
                    return "";
                }
            }

            static std::string get_action_string(enum StateActions _action) {
                switch (_action) {
                    /* Initialization mode actions */
                case StateActions::START_SETUP:
                    return "START_SETUP";
                case StateActions::FINISH_SETUP:
                    return "FINISH_SETUP";

                    /* Parsing mode actions */
                case StateActions::START_PARSING_SETTINGS:
                    return "START_PARSING_SETTINGS";
                case StateActions::FINISH_PARSING_SETTINGS:
                    return "FINISH_PARSING_SETTINGS";
                case StateActions::START_PARSING_QUESTS_INDEX:
                    return "START_PARSING_QUESTS_INDEX";
                case StateActions::FINISH_PARSING_QUESTS_INDEX:
                    return "FINISH_PARSING_QUESTS_INDEX";
                case StateActions::START_PARSING_QUEST_FILE:
                    return "START_PARSING_QUEST_FILE";
                case StateActions::FINISH_PARSING_QUEST_FILE:
                    return "FINISH_PARSING_QUEST_FILE";

                    /* Quest mode actions */
                case StateActions::START_QUEST:
                    return "START_QUEST";
                case StateActions::END_QUEST:
                    return "END_QUEST";
                case StateActions::QUEST_START_TURN:
                    return "QUEST_START_TURN";
                case StateActions::QUEST_DECIDE_ACTIONS:
                    return "QUEST_DECIDE_ACTIONS";
                case StateActions::QUEST_START_PERFORM_ACTIONS:
                    return "QUEST_START_PERFORM_ACTIONS";
                case StateActions::QUEST_FINISH_PERFORM_ACTIONS:
                    return "QUEST_FINISH_PERFORM_ACTIONS";

                    /* Menu mode actions */
                case StateActions::OPEN_MAIN_MENU:
                    return "OPEN_MAIN_MENU";
                case StateActions::CLOSE_MAIN_MENU:
                    return "CLOSE_MAIN_MENU";
                case StateActions::OPEN_PLAY_SUBMENU:
                    return "OPEN_PLAY_SUBMENU";
                case StateActions::CLOSE_PLAY_SUBMENU:
                    return "CLOSE_PLAY_SUBMENU";
                case StateActions::WARN_NEWSAVE_PLAY_SUBMENU:
                    return "WARN_NEWSAVE_PLAY_SUBMENU";
                case StateActions::CLOSE_WARN_NEWSAVE_PLAY_SUBMENU:
                    return "CLOSE_WARN_NEWSAVE_PLAY_SUBMENU";
                case StateActions::OPEN_SETTINGS_SUBMENU:
                    return "OPEN_SETTINGS_SUBMENU";
                case StateActions::CLOSE_SETTINGS_SUBMENU:
                    return "CLOSE_SETTINGS_SUBMENU";
                default:
                    return "";
                }
            }
        };
    }
}