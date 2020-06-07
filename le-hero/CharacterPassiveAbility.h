/**
 * CharacterPassiveAbility.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterElement.h"

namespace le_hero {
    struct CharacterPassiveAbility {
        std::string name;
        std::string effect;
        enum CharacterElements native_element = CharacterElements::BASIC;
    };
}