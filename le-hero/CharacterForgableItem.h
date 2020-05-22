/**
 * CharacterForgableItem.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterItem.h"

namespace le_hero {
    typedef struct {
        uint8_t base_item = 0;
        uint32_t forge_cost = 0;
        uint8_t required_item_left = 0;
        uint8_t required_item_right = 0;

        bool requires_triple = false;
        uint8_t required_item_center = 0;
    } CharacterForgableItem;
}