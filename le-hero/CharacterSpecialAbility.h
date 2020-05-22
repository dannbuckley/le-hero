/**
 * CharacterSpecialAbility.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <cstdint>
#include <string>

namespace le_hero {
    typedef struct {
        bool melee_range_weapon_needed;
        bool long_range_weapon_needed;

        bool basic_element_supported;
        bool earth_element_supported;
        bool air_element_supported;
        bool fire_element_supported;
        bool water_element_supported;
        bool mystic_element_supported;
    } CharacterSpecialAbilityRequirements;

    typedef struct {
        uint8_t index = 0;
        std::string name;
        std::string effect;
        uint16_t cost_to_learn = 0;
        CharacterSpecialAbilityRequirements requirements = CharacterSpecialAbilityRequirements {};
    } CharacterSpecialAbility;
}