/**
 * Game.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <exception>
#include <imgui.h>
#include "Game.h"
#include "GameExceptions.h"
#include "StateStack.h"
#include "spdlog/spdlog.h"

namespace le_hero {
    namespace game {
        /* Game State Machine */

        StateStack state_handler;

        /* Game Data */

        std::vector<CharacterElement> elements;
        std::vector<CharacterRank> ranks;
        std::vector<CharacterStatus> statuses;
        std::vector<CharacterWeapon> weapons;
        std::vector<CharacterPassiveAbility> passive_abilities;
        std::vector<CharacterSpecialAbility> special_abilities;

        /* Quest Data */

        std::vector<std::pair<std::string, std::string>> quest_references;

        /* Debug Variables */

        std::vector<std::string> state_history;
        std::vector<std::string> action_history;

        void initialize_game_environment(const char* settings_file) {
            lua::LuaHandler lua_handler;

            game_act(StateActions::START_SETUP);
            game_act(StateActions::START_PARSING_SETTINGS);

            // parse base game settings file
            std::string quests_index_file;
            bool parse_result = lua_handler.parse_settings_file(settings_file,
                quests_index_file,
                elements,
                ranks,
                statuses,
                weapons,
                passive_abilities,
                special_abilities);

            // check if the base settings file has been parsed properly
            if (!parse_result) {
                throw exception::unsuccessful_lua_parse_error();
            }

            game_act(StateActions::FINISH_PARSING_SETTINGS);
            spdlog::get("logger")->info("Game settings parsed successfully.");
            game_act(StateActions::START_PARSING_QUESTS_INDEX);

            // parse quests index file
            parse_result = lua_handler.parse_quests_index_file(quests_index_file, quest_references);

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
            state_handler.push(new_state);

            // log state change
            spdlog::get("logger")->debug("Changed to {} state (value {})", state::get_state_string(new_state), new_state);
            return true;
        }

        // Exits the current state and logs it for debugging
        bool exit_current_state()
        {
            if (state_handler.is_empty()) {
                return false;
            }

            // save current state and remove from state stack
            auto last_state = state_handler.peek();
            state_handler.pop();

            // record previous state for debugging
            state_history.push_back(get_state_string(last_state));
            spdlog::get("logger")->debug("Exited {} state (value {})", state_history.back(), last_state);
            return true;
        }

        // Handles game_act() calls while in stateless mode
        bool act_in_stateless(enum StateActions action) {
            spdlog::get("logger")->debug("Called game::act_in_stateless({}) (value {})", state::get_action_string(action), action);
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
            spdlog::get("logger")->debug("Called game::act_in_initializing({}) (value {})", state::get_action_string(action), action);
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
            spdlog::get("logger")->debug("Called game::act_in_parsing({}) (value {})", state::get_action_string(action), action);
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
            spdlog::get("logger")->debug("Called game::act_in_quest({}) (value {})", state::get_action_string(action), action);
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
            spdlog::get("logger")->debug("Called game::act_in_menu({}) (value {})", state::get_action_string(action), action);
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
            action_history.push_back(get_action_string(action));
            spdlog::get("logger")->debug("Called game::game_act({}) (value {})", action_history.back(), action);

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

        // Returns the current state of the game environment
        enum StateTypes get_current_state() {
            if (state_handler.is_empty()) {
                return StateTypes::STATELESS;
            }
            else {
                return state_handler.peek();
            }
        }

        // Renders an ImGui window for viewing current game states and state/action history
        void render_state_window()
        {
            ImGui::Begin("Game State");
            if (ImGui::TreeNode("State History")) {
                for (const auto& s : state_history) {
                    ImGui::Text(s.c_str());
                }
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Action History")) {
                for (const auto& a : action_history) {
                    ImGui::Text(a.c_str());
                }
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("State Stack")) {
                for (const auto& s : state_handler.get_display_vector()) {
                    ImGui::Text(s.c_str());
                }
                ImGui::TreePop();
            }
            ImGui::End();
        }

        // Renders an ImGui window for viewing currently loaded character assets
        void render_character_assets_window() {
            ImGui::Begin("Character Assets");
            if (ImGui::CollapsingHeader("Elements")) {
                for (const auto& e : elements) {
                    if (ImGui::TreeNode(e.name.c_str())) {
                        ImGui::Text("Base Attack: %d", e.base_attack);
                        ImGui::Text("Base Speed: %d", e.base_speed);
                        ImGui::Text("Base Health: %d", e.base_health);
                        ImGui::TreePop();
                    }
                }
            }
            if (ImGui::CollapsingHeader("Ranks")) {
                for (const auto& r : ranks) {
                    if (ImGui::TreeNode(r.name.c_str())) {
                        ImGui::Text("Attack Boost: %d", r.attack_boost);
                        ImGui::Text("Speed Boost: %d", r.speed_boost);
                        ImGui::Text("Health Boost: %d", r.health_boost);
                        ImGui::TreePop();
                    }
                }
            }
            if (ImGui::CollapsingHeader("Statuses")) {
                for (const auto& st : statuses) {
                    if (ImGui::TreeNode(st.name.c_str())) {
                        ImGui::Text("Effect: %s", st.effect.c_str());
                        ImGui::Text("Effect Length: %d", st.effect_length);
                        ImGui::TreePop();
                    }
                }
            }
            if (ImGui::CollapsingHeader("Weapons")) {
                for (const auto& w : weapons) {
                    if (ImGui::TreeNode(w.name.c_str())) {
                        ImGui::Text("Element: %d", w.element);
                        ImGui::Text("Strength: %d", w.strength);
                        ImGui::Text("Category: %d", w.category);
                        ImGui::Text("Handling: %d", w.handling);
                        ImGui::Text("Weight: %d", w.weight);
                        ImGui::Text("Range: %d", w.range);
                        ImGui::Text("Damage Type: %d", w.damage_type);
                        ImGui::TreePop();
                    }
                }
            }
            if (ImGui::CollapsingHeader("Passive Abilities")) {
                for (const auto& p : passive_abilities) {
                    if (ImGui::TreeNode(p.name.c_str())) {
                        ImGui::Text("Effect: %s", p.effect.c_str());
                        ImGui::TreePop();
                    }
                }
            }
            if (ImGui::CollapsingHeader("Special Abilities")) {
                for (const auto& sp : special_abilities) {
                    if (ImGui::TreeNode(sp.name.c_str())) {
                        ImGui::Text("Effect: %s", sp.effect.c_str());
                        ImGui::TreePop();
                    }
                }
            }
            ImGui::End();
        }

        // Renders ImGui windows for the game environment
        void render_imgui_windows()
        {
            render_state_window();
            render_character_assets_window();
        }

        // Returns data for requested character element
        const CharacterElement& get_element(uint8_t index) {
            return elements[index];
        }

        // Returns data for requested character rank
        const CharacterRank& get_rank(uint8_t index) {
            return ranks[index];
        }

        // Returns data for requested character status
        const CharacterStatus& get_status(uint8_t index) {
            return statuses[index];
        }

        // Returns data for requested character weapon
        const CharacterWeapon& get_weapon(uint8_t index) {
            return weapons[index];
        }

        // Returns data for requested character passive ability
        const CharacterPassiveAbility& get_passive_ability(uint8_t index) {
            return passive_abilities[index];
        }

        // Returns data for requested character special ability
        const CharacterSpecialAbility& get_special_ability(uint8_t index) {
            return special_abilities[index];
        }

        // Returns pair containing name and file location for the requested quest
        const std::pair<std::string, std::string>& get_quest_ref(uint8_t index) {
            return quest_references[index];
        }

        // Returns the number of character statuses
        const size_t get_num_statuses() {
            return statuses.size();
        }

        // Returns the number of character weapons
        const size_t get_num_weapons() {
            return weapons.size();
        }

        // Returns the number of character special abilities
        const size_t get_num_special_abilities() {
            return special_abilities.size();
        }

        // Returns the number of quest reference pairs
        const size_t get_num_quest_refs() {
            return quest_references.size();
        }
    }
}