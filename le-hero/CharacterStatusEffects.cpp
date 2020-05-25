/**
 * CharacterStatusEffects.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <algorithm>
#include <cmath>
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
                return CharacterStatusEffects::frenzy_status_effect(self);
            default:
                // not a valid status
                return false;
            }
        }

        namespace status {
            /* Health-influence statuses */

            bool CharacterStatusEffects::burn_status_effect(CharacterBattleHandler* self)
            {
                uint16_t max_health = self->get_maximum_health();
                uint16_t damage = std::max((uint16_t)ceilf(max_health * 0.01f), (uint16_t)1);
                self->damage_health(damage, true);
                return true;
            }

            bool CharacterStatusEffects::poison_status_effect(CharacterBattleHandler* self)
            {
                uint16_t max_health = self->get_maximum_health();
                uint16_t damage = std::max((uint16_t)ceilf(max_health * 0.03f), (uint16_t)1);
                self->damage_health(damage, true);
                return true;
            }

            bool CharacterStatusEffects::enlightened_status_effect(CharacterBattleHandler* self)
            {
                uint16_t max_health = self->get_maximum_health();
                uint16_t heal_val = std::max((uint16_t)floorf(max_health * 0.1f), (uint16_t)1);
                self->restore_health(heal_val);
                return true;
            }

            bool CharacterStatusEffects::guarding_status_effect(CharacterBattleHandler* self)
            {
                self->protect_from_damage();
                return true;
            }

            /* Attack-influence statuses */

            bool CharacterStatusEffects::mystified_status_effect(CharacterBattleHandler* self)
            {
                self->lock_on_pass();
                return true;
            }

            bool CharacterStatusEffects::enraged_status_effect(CharacterBattleHandler* self)
            {
                self->lock_on_weapon();
                return true;
            }

            bool CharacterStatusEffects::weightless_status_effect(CharacterBattleHandler* self)
            {
                if (self->get_equipped_weapon().range == WeaponRange::MELEE) {
                    self->disable_weapon();
                    return true;
                }

                // return false if status had no effect
                return false;
            }

            bool CharacterStatusEffects::claustrophobic_status_effect(CharacterBattleHandler* self)
            {
                if (self->get_equipped_weapon().range == WeaponRange::LONG) {
                    self->disable_weapon();
                    return true;
                }
                // return false if status had no effect
                return false;
            }

            bool CharacterStatusEffects::frozen_status_effect(CharacterBattleHandler* self)
            {
                self->lock_on_pass();
                return true;
            }

            bool CharacterStatusEffects::amnesiac_status_effect(CharacterBattleHandler* self)
            {
                self->disable_special();
                return true;
            }

            /* Armor-influence statuses */

            bool CharacterStatusEffects::shattered_armor_status_effect(CharacterBattleHandler* self)
            {
                if (self->get_armor_turns_left() > 0) {
                    self->remove_armor();
                    return true;
                }

                // return false if status had no effect
                return false;
            }

            /* Multi-influence statuses */

            bool CharacterStatusEffects::unworthy_status_effect(CharacterBattleHandler* self)
            {
                self->remove_armor();
                self->lock_on_pass();

                uint16_t max_health = self->get_maximum_health();
                uint16_t damage = std::max((uint16_t)floorf(max_health * 0.5f), (uint16_t)1);
                self->damage_health(damage, true);
                return true;
            }

            bool CharacterStatusEffects::protecting_status_effect(CharacterBattleHandler* self)
            {
                self->protect_from_damage();
                self->disable_special();
                return true;
            }

            bool CharacterStatusEffects::frenzy_status_effect(CharacterBattleHandler* self)
            {
                self->apply_attack_modifier(1.8f);
                self->apply_speed_modifier(1.8f);

                uint16_t heal_val = std::max((uint16_t)ceilf(self->get_damage_dealt() * 0.4f), (uint16_t)1);
                self->restore_health(heal_val);

                self->disable_special();
                return true;
            }
        }
    }
}