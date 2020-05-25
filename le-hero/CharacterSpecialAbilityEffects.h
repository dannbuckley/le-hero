/**
 * CharacterSpecialAbilityEffects.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterEffectFunctions.h"

namespace le_hero {
    namespace effect {
        namespace special_ability {
            class CharacterSpecialAbilityEffects
            {
            public:
                static bool protect_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool recovery_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool tricky_mirror_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool revenge_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool deadly_accuracy_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool flaming_vortex_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool inferno_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool hurricane_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool whirlpool_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool landslide_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool extinguish_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool scald_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool speedster_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool power_trick_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool platinum_power_play_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool guard_stance_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool honor_amongst_thieves_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool good_samaritan_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
                static bool call_to_arms_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
            };
        }
    }
}