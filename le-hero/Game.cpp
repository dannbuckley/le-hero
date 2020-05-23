/**
 * Game.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <exception>
#include "Game.h"
#include "spdlog/spdlog.h"

namespace le_hero {
    struct unsuccessful_lua_parse_error : public std::exception {
        const char* what() const throw() {
            return "Encountered an error while parsing the Lua game settings file. See 'log.txt' for more info.";
        }
    };

    // Handles act() calls while in stateless mode
    bool Game::act_in_stateless(enum state::StateActions action)
    {
        spdlog::get("logger")->debug("Called Game::act_in_stateless({})", action);
        switch (action) {
        case state::StateActions::START_SETUP:
            // enter initialization mode
            this->state_handler->push(state::StateTypes::INITIALIZING);

            // log state change
            spdlog::get("logger")->debug("Changed to INITIALIZING state (value {})", (int)state::StateTypes::INITIALIZING);
            return true;
        default:
            // not a valid action in stateless mode
            return false;
        }
    }

    // Handles act() calls while in initialization mode
    bool Game::act_in_initializing(enum state::StateActions action)
    {
        spdlog::get("logger")->debug("Called Game::act_in_initialization({})", action);
        switch (action) {
        case state::StateActions::FINISH_SETUP:
            // exit initialization mode
            this->exit_current_state();

            // log state change
            spdlog::get("logger")->debug("Exited INITIALIZING state (value {})", (int)state::StateTypes::INITIALIZING);
            return true;
        default:
            // not a valid action in initialization mode
            return false;
        }
    }

    // Exits the current state and logs it for debugging
    bool Game::exit_current_state()
    {
        if (this->state_handler->empty()) {
            return false;
        }

        // save current state and remove from state stack
        auto last_state = this->state_handler->top();
        this->state_handler->pop();

        // record previous state for debugging
        this->state_history.push_back(last_state);
        return true;
    }

    Game::Game(std::string settings_file)
    {
        state_handler = std::make_unique<std::stack<enum state::StateTypes>>();

        this->act(state::StateActions::START_SETUP);
        lua_handler = std::make_unique<lua::LuaHandler>();
        bool parse_result = lua_handler->parse_settings_file(settings_file,
            elements,
            ranks,
            statuses,
            weapons,
            passive_abilities,
            special_abilities,
            items);

        // check if the settings file has been parsed properly
        if (!parse_result) {
            throw unsuccessful_lua_parse_error();
        }

        this->act(state::StateActions::FINISH_SETUP);
    }

    CharacterElement Game::get_element(uint8_t index)
    {
        return elements[index];
    }

    CharacterRank Game::get_rank(uint8_t index)
    {
        return ranks[index];
    }

    CharacterStatus Game::get_status(uint8_t index)
    {
        return statuses[index];
    }

    CharacterWeapon Game::get_weapon(uint8_t index)
    {
        return weapons[index];
    }

    CharacterPassiveAbility Game::get_passive_ability(uint8_t index)
    {
        return passive_abilities[index];
    }

    CharacterSpecialAbility Game::get_special_ability(uint8_t index)
    {
        return special_abilities[index];
    }

    CharacterItem Game::get_item(uint8_t index)
    {
        return items[index];
    }

    size_t Game::get_num_statuses()
    {
        return statuses.size();
    }

    size_t Game::get_num_weapons()
    {
        return weapons.size();
    }

    size_t Game::get_num_special_abilities()
    {
        return special_abilities.size();
    }

    size_t Game::get_num_items()
    {
        return items.size();
    }

    // Handles state actions and logs them for debugging
    bool Game::act(enum state::StateActions action)
    {
        // record action for debugging
        this->action_history.push_back(action);
        spdlog::get("logger")->debug("Called Game::act({})", action);

        // determine current state and perform action
        switch (this->get_current_state()) {
        case state::StateTypes::STATELESS:
            return act_in_stateless(action);
        case state::StateTypes::INITIALIZING:
            return act_in_initializing(action);
        default:
            return false;
        }
    }

    // Returns the state located at the top of the state_handler stack
    // or StateTypes::STATELESS if the stack is empty
    state::StateTypes Game::get_current_state()
    {
        if (this->state_handler->empty()) {
            return state::StateTypes::STATELESS;
        }
        else {
            return this->state_handler->top();
        }
    }
}
