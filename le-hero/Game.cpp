/**
 * Game.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "Game.h"

namespace le_hero {
    Game::Game(std::string settings_file)
    {
        lua_handler = std::make_unique<lua::LuaHandler>();
        lua_handler->parse_settings_file(settings_file,
            elements,
            ranks,
            statuses,
            weapons,
            passive_abilities,
            special_abilities,
            items);
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
}
