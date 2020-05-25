/**
 * CharacterStatusEffects.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "CharacterStatusEffects.h"

namespace le_hero {
    namespace effect {
        bool activate_status_effect(CharacterBattleHandler* self)
        {
            using namespace status;

            auto inflicted_status = self->get_inflicted_status();

            switch (inflicted_status.index) {
            case 0:
                return CharacterStatusEffects::burn_status_effect(self);
            case 1:
                return CharacterStatusEffects::poison_status_effect(self);
            case 2:
                return CharacterStatusEffects::enlightened_status_effect(self);
            case 3:
                return CharacterStatusEffects::guarding_status_effect(self);
            case 4:
                return CharacterStatusEffects::mystified_status_effect(self);
            case 5:
                return CharacterStatusEffects::enraged_status_effect(self);
            case 6:
                return CharacterStatusEffects::weightless_status_effect(self);
            case 7:
                return CharacterStatusEffects::claustrophobic_status_effect(self);
            case 8:
                return CharacterStatusEffects::frozen_status_effect(self);
            case 9:
                return CharacterStatusEffects::amnesiac_status_effect(self);
            case 10:
                return CharacterStatusEffects::shattered_armor_status_effect(self);
            case 11:
                return CharacterStatusEffects::unworthy_status_effect(self);
            case 12:
                return CharacterStatusEffects::protecting_status_effect(self);
            case 13:
                return CharacterStatusEffects::killing_spree_status_effect(self);
            default:
                // not a valid status
                return false;
            }
        }

        namespace status {
            bool CharacterStatusEffects::burn_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::poison_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::enlightened_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::guarding_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::mystified_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::enraged_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::weightless_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::claustrophobic_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::frozen_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::amnesiac_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::shattered_armor_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::unworthy_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::protecting_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }

            bool CharacterStatusEffects::killing_spree_status_effect(CharacterBattleHandler* self)
            {
                return false;
            }
        }
    }
}