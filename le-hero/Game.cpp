/**
 * Game.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <exception>
#include <stack>
#include "Game.h"
#include "GameExceptions.h"
#include "spdlog/spdlog.h"

namespace le_hero {
    namespace game {
        std::unique_ptr<std::stack<enum StateTypes>> state_handler;

        /* Game Data */

        std::vector<CharacterElement> elements;
        std::vector<CharacterRank> ranks;
        std::vector<CharacterStatus> statuses;
        std::vector<CharacterWeapon> weapons;
        std::vector<CharacterPassiveAbility> passive_abilities;
        std::vector<CharacterSpecialAbility> special_abilities;
        std::vector<CharacterItem> items;

        /* Quest Data */

        std::vector<std::pair<std::string, std::string>> quest_references;

        /* Debug Variables */

        std::vector<enum StateTypes> state_history;
        std::vector<enum StateActions> action_history;

        void initialize_game_environment(const char* settings_file) {
            state_handler = std::make_unique<std::stack<enum StateTypes>>();
            std::unique_ptr<lua::LuaHandler> lua_handler = std::make_unique<lua::LuaHandler>();

            game_act(StateActions::START_SETUP);
            game_act(StateActions::START_PARSING_SETTINGS);

            // parse base game settings file
            std::string quests_index_file;
            bool parse_result = lua_handler->parse_settings_file(settings_file,
                quests_index_file,
                elements,
                ranks,
                statuses,
                weapons,
                passive_abilities,
                special_abilities,
                items);

            // check if the base settings file has been parsed properly
            if (!parse_result) {
                throw exception::unsuccessful_lua_parse_error();
            }

            game_act(StateActions::FINISH_PARSING_SETTINGS);
            spdlog::get("logger")->info("Game settings parsed successfully.");
            game_act(StateActions::START_PARSING_QUESTS_INDEX);

            // parse quests index file
            parse_result = lua_handler->parse_quests_index_file(quests_index_file, quest_references);

            // check if the quests index file has been parsed properly
            if (!parse_result) {
                throw exception::unsuccessful_lua_parse_error();
            }

            game_act(StateActions::FINISH_PARSING_QUESTS_INDEX);
            spdlog::get("logger")->info("References to quest data parsed successfully.");
            game_act(StateActions::FINISH_SETUP);
        }

        // Enters the provided state and logs it for debugging
        bool enter_state(enum StateTypes new_state)
        {
            // enter new state
            state_handler->push(new_state);

            // log state change
            spdlog::get("logger")->debug("Changed to {} state (value {})", StateHandler::get_state_string(new_state), new_state);
            return true;
        }

        // Exits the current state and logs it for debugging
        bool exit_current_state()
        {
            if (state_handler->empty()) {
                return false;
            }

            // save current state and remove from state stack
            auto last_state = state_handler->top();
            state_handler->pop();

            // record previous state for debugging
            state_history.push_back(last_state);
            spdlog::get("logger")->debug("Exited {} state (value {})", StateHandler::get_state_string(last_state), last_state);
            return true;
        }

        // Handles game_act() calls while in stateless mode
        bool act_in_stateless(enum StateActions action) {
            spdlog::get("logger")->debug("Called game::act_in_stateless({}) (value {})", StateHandler::get_action_string(action), action);
            switch (action) {
            case StateActions::START_SETUP:
                // enter initialization mode
                return enter_state(StateTypes::INITIALIZING);

            case StateActions::START_PARSING_QUEST_FILES:
                // enter parsing mode
                return enter_state(StateTypes::PARSING_QUEST_FILES);

            case StateActions::START_QUEST:
                // enter quest mode
                return enter_state(StateTypes::EMBARKING_ON_QUEST);

            case StateActions::OPEN_MAIN_MENU:
                // enter menu mode
                return enter_state(StateTypes::MAIN_MENU);

            default:
                // not a valid action in stateless mode
                return false;
            }
        }

        // Handles game_act() calls while in initialization mode
        bool act_in_initializing(enum StateActions action) {
            spdlog::get("logger")->debug("Called game::act_in_initializing({}) (value {})", StateHandler::get_action_string(action), action);
            switch (action) {
            case StateActions::FINISH_SETUP:
                // exit initialization mode
                return exit_current_state();

            case StateActions::START_PARSING_SETTINGS:
                // enter parsing mode
                return enter_state(StateTypes::PARSING_SETTINGS);

            case StateActions::START_PARSING_QUESTS_INDEX:
                // enter parsing mode
                return enter_state(StateTypes::PARSING_QUESTS_INDEX);

            default:
                // not a valid action in initialization mode
                return false;
            }
        }

        // Handles game_act() calls while in parsing mode
        bool act_in_parsing(enum StateActions action) {
            spdlog::get("logger")->debug("Called game::act_in_parsing({}) (value {})", StateHandler::get_action_string(action), action);
            switch (action) {
            case StateActions::FINISH_PARSING_SETTINGS:
            case StateActions::FINISH_PARSING_QUESTS_INDEX:
            case StateActions::FINISH_PARSING_QUEST_FILES:
                // exit parsing mode
                return exit_current_state();

            default:
                // not a valid action in parsing mode
                return false;
            }
        }

        // Handles game_act() calls while in quest mode
        bool act_in_quest(enum StateActions action) {
            spdlog::get("logger")->debug("Called game::act_in_quest({}) (value {})", StateHandler::get_action_string(action), action);
            switch (action) {
            case StateActions::END_QUEST:
                // exit quest mode
                return exit_current_state();

            case StateActions::QUEST_START_TURN:
                // enter quest "awaiting character actions" state
                return enter_state(StateTypes::QUEST_AWAITING_ACTIONS);

            case StateActions::QUEST_DECIDE_ACTIONS:
                // switch states from QUEST_AWAITING_ACTIONS to QUEST_READY_FOR_TURN
                exit_current_state();
                return enter_state(StateTypes::QUEST_READY_FOR_TURN);

            case StateActions::QUEST_START_PERFORM_ACTIONS:
                // enter quest "performing actions" state
                exit_current_state(); // exit QUEST_READY_FOR_TURN
                return enter_state(StateTypes::QUEST_PERFORMING_ACTIONS);

            case StateActions::QUEST_FINISH_PERFORM_ACTIONS:
                // exit quest "performing actions" state
                return exit_current_state();

            default:
                // not a valid action in quest mode
                return false;
            }
        }

        // Handles game_act() calls while in menu mode
        bool act_in_menu(enum StateActions action) {
            spdlog::get("logger")->debug("Called game::act_in_menu({}) (value {})", StateHandler::get_action_string(action), action);
            switch (action) {
            case StateActions::CLOSE_MAIN_MENU:
            case StateActions::CLOSE_PLAY_SUBMENU:
            case StateActions::CLOSE_WARN_NEWSAVE_PLAY_SUBMENU:
            case StateActions::CLOSE_SETTINGS_SUBMENU:
                // exit current menu
                return exit_current_state();

            case StateActions::OPEN_PLAY_SUBMENU:
                // enter "Play" submenu
                return enter_state(StateTypes::MAIN_PLAY_SUBMENU);

            case StateActions::WARN_NEWSAVE_PLAY_SUBMENU:
                // enter "New save will overwrite all data" warning
                return enter_state(StateTypes::MAIN_PLAY_NEWSAVE_WARNING);

            case StateActions::OPEN_SETTINGS_SUBMENU:
                // enter "Settings" submenu
                return enter_state(StateTypes::MAIN_SETTINGS_SUBMENU);

            default:
                // not a valid action in menu mode
                return false;
            }
        }

        // Handles state actions and logs them for debugging
        bool game_act(enum StateActions action) {
            // record action for debugging
            action_history.push_back(action);
            spdlog::get("logger")->debug("Called game::game_act({}) (value {})", StateHandler::get_action_string(action), action);

            // determine current state and perform action
            switch (get_current_state()) {
            case StateTypes::STATELESS:
                return act_in_stateless(action);

            case StateTypes::INITIALIZING:
                return act_in_initializing(action);

            case StateTypes::PARSING_SETTINGS:
            case StateTypes::PARSING_QUESTS_INDEX:
            case StateTypes::PARSING_QUEST_FILES:
                return act_in_parsing(action);

            case StateTypes::EMBARKING_ON_QUEST:
            case StateTypes::QUEST_AWAITING_ACTIONS:
            case StateTypes::QUEST_READY_FOR_TURN:
            case StateTypes::QUEST_PERFORMING_ACTIONS:
                return act_in_quest(action);

            case StateTypes::MAIN_MENU:
            case StateTypes::MAIN_PLAY_SUBMENU:
            case StateTypes::MAIN_PLAY_NEWSAVE_WARNING:
            case StateTypes::MAIN_SETTINGS_SUBMENU:
                return act_in_menu(action);
            default:
                // not a valid state
                return false;
            }
        }

        enum StateTypes get_current_state() {
            if (state_handler->empty()) {
                return StateTypes::STATELESS;
            }
            else {
                return state_handler->top();
            }
        }

        const CharacterElement& get_element(uint8_t index) {
            return elements[index];
        }

        const CharacterRank& get_rank(uint8_t index) {
            return ranks[index];
        }

        const CharacterStatus& get_status(uint8_t index) {
            return statuses[index];
        }

        const CharacterWeapon& get_weapon(uint8_t index) {
            return weapons[index];
        }

        const CharacterPassiveAbility& get_passive_ability(uint8_t index) {
            return passive_abilities[index];
        }

        const CharacterSpecialAbility& get_special_ability(uint8_t index) {
            return special_abilities[index];
        }

        const CharacterItem& get_item(uint8_t index) {
            return items[index];
        }

        const std::pair<std::string, std::string>& get_quest_ref(uint8_t index) {
            return quest_references[index];
        }

        const size_t get_num_statuses() {
            return statuses.size();
        }

        const size_t get_num_weapons() {
            return weapons.size();
        }
        const size_t get_num_special_abilities() {
            return special_abilities.size();
        }

        const size_t get_num_items() {
            return items.size();
        }

        const size_t get_num_quest_refs() {
            return quest_references.size();
        }
    }
}