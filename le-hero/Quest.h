/**
 * Quest.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "Character.h"

namespace le_hero {
    namespace quest {
        struct Quest {
            std::string name;
            std::string description;
            enum CharacterElements quest_terrain = CharacterElements::BASIC;
            std::vector<CharacterMeta> enemy_info;
        };

        struct QuestEnemyInfo {
            uint8_t enemy_index = 0;
            CharacterMeta enemy_meta;
        };
    }
}