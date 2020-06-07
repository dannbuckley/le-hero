/**
 * CharacterItem.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterElement.h"

namespace le_hero {
    enum class CharacterItemType : uint8_t {
        ITEM_ENHANCEMENT = 0,
        ITEM_RECOVERY,
        ITEM_UPGRADE,
        ITEM_BATTLE,
        ITEM_EQUIP,
    };

    enum class CharacterItemRank : uint8_t {
        NO_ITEM_RANK = 0,
        ITEM_RANK_1,
        ITEM_RANK_2,
        ITEM_RANK_3,
        ITEM_RANK_A,
    };

    struct CharacterItem {
        std::string name;
        std::string effect;
        enum CharacterItemType item_type = CharacterItemType::ITEM_ENHANCEMENT;
        enum CharacterItemRank item_rank = CharacterItemRank::NO_ITEM_RANK;
        enum CharacterElements item_element = CharacterElements::BASIC;
        uint32_t cost = 0;
        uint8_t available_at_level = 0;
    };
}