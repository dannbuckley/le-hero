/**
 * CharacterPassiveAbility.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterElement.h"

namespace le_hero {
    typedef struct {
        std::string name;
        std::string effect;
        enum CharacterElements native_element = CharacterElements::BASIC;
    } CharacterPassiveAbility;
}