/**
 * CharacterItemEffects.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterEffectFunctions.h"
#include "CharacterItem.h"

namespace le_hero {
    namespace effect {
        namespace item {
            class CharacterItemEffects
            {
            public:
                static bool exp_spell_item_effect(CharacterBattleHandler* self, enum CharacterItemRank item_rank);
                static bool elemental_exp_spell_item_effect(CharacterBattleHandler* self, enum CharacterItemRank item_rank, enum CharacterElements item_element);
                static bool energy_orb_effect(CharacterBattleHandler* self, enum CharacterElements item_element);
                static bool steel_plate_item_effect(CharacterBattleHandler* self);
                static bool curing_spell_item_effect(CharacterBattleHandler* self);
                static bool healing_spell_item_effect(CharacterBattleHandler* self, enum CharacterItemRank item_rank);
            };
        }
    }
}