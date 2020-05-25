/**
 * CharacterStatusEffects.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterEffectFunctions.h"

namespace le_hero {
    namespace effect {
        namespace status {
            class CharacterStatusEffects
            {
            public:
                /* Health-influence statuses */

                static bool burn_status_effect(CharacterBattleHandler* self);
                static bool poison_status_effect(CharacterBattleHandler* self);
                static bool enlightened_status_effect(CharacterBattleHandler* self);
                static bool guarding_status_effect(CharacterBattleHandler* self);

                /* Attack-influence statuses */

                static bool mystified_status_effect(CharacterBattleHandler* self);
                static bool enraged_status_effect(CharacterBattleHandler* self);
                static bool weightless_status_effect(CharacterBattleHandler* self);
                static bool claustrophobic_status_effect(CharacterBattleHandler* self);
                static bool frozen_status_effect(CharacterBattleHandler* self);
                static bool amnesiac_status_effect(CharacterBattleHandler* self);

                /* Armor-influence statuses */

                static bool shattered_armor_status_effect(CharacterBattleHandler* self);

                /* Multi-influence statuses */

                static bool unworthy_status_effect(CharacterBattleHandler* self);
                static bool protecting_status_effect(CharacterBattleHandler* self);
                static bool frenzy_status_effect(CharacterBattleHandler* self);
            };
        }
    }
}