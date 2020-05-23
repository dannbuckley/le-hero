/**
 * Quest.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "Character.h"

namespace le_hero {
    namespace quest {
        typedef struct {
            std::string name;
            std::string description;
            std::vector<CharacterMeta> enemy_info;
            uint8_t recommended_level = 0;
            enum CharacterElements quest_terrain = CharacterElements::BASIC;
            uint32_t prize_coins = 0;
            uint16_t prize_experience = 0;
            std::vector<uint8_t> prize_items;
            std::vector<uint8_t> prize_weapons;
        } Quest;

        typedef struct {
            uint8_t enemy_index = 0;
            CharacterMeta enemy_meta;
        } QuestEnemyInfo;
    }
}