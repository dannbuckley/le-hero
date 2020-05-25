/**
 * CharacterPassiveAbilityEffects.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterEffectFunctions.h"

namespace le_hero {
    namespace effect {
        namespace passive_ability {
            class CharacterPassiveAbilityEffects
            {
            public:
                static bool basic_passive_effect(std::shared_ptr<CharacterBattleHandler> self);
                static bool earth_passive_effect(std::shared_ptr<CharacterBattleHandler> self);
                static bool air_passive_effect(std::shared_ptr<CharacterBattleHandler> self);
                static bool fire_passive_effect(std::shared_ptr<CharacterBattleHandler> self);
                static bool water_passive_effect(std::shared_ptr<CharacterBattleHandler> self);
                static bool mystic_passive_effect(std::shared_ptr<CharacterBattleHandler> self);
                static bool alpha_passive_effect(std::shared_ptr<CharacterBattleHandler> self);
            };
        }
    }
}