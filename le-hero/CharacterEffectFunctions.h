/**
 * CharacterEffectFunctions.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterBattleHandler.h"

namespace le_hero {
    namespace effect {
        extern bool activate_passive_ability_effect(std::shared_ptr<CharacterBattleHandler> self);
        extern bool activate_special_ability_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
        extern bool activate_status_effect(CharacterBattleHandler* self);
        extern bool activate_item_effect(uint8_t index, CharacterBattleHandler* self);
    }
}