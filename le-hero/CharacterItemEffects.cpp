/**
 * CharacterItemEffects.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <algorithm>
#include <cmath>
#include "CharacterItemEffects.h"

namespace le_hero {
    namespace effect {
        bool activate_item_effect(uint8_t index, CharacterBattleHandler* self)
        {
            using namespace item;

            switch (index) {
            case 0:
                return CharacterItemEffects::exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_1);
            case 1:
                return CharacterItemEffects::exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_2);
            case 2:
                return CharacterItemEffects::exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_3);
            case 3:
                return CharacterItemEffects::exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_A);
            case 4:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_1, CharacterElements::EARTH);
            case 5:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_2, CharacterElements::EARTH);
            case 6:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_3, CharacterElements::EARTH);
            case 7:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_A, CharacterElements::EARTH);
            case 8:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_1, CharacterElements::AIR);
            case 9:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_2, CharacterElements::AIR);
            case 10:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_3, CharacterElements::AIR);
            case 11:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_A, CharacterElements::AIR);
            case 12:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_1, CharacterElements::FIRE);
            case 13:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_2, CharacterElements::FIRE);
            case 14:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_3, CharacterElements::FIRE);
            case 15:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_A, CharacterElements::FIRE);
            case 16:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_1, CharacterElements::WATER);
            case 17:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_2, CharacterElements::WATER);
            case 18:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_3, CharacterElements::WATER);
            case 19:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_A, CharacterElements::WATER);
            case 20:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_1, CharacterElements::MYSTIC);
            case 21:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_2, CharacterElements::MYSTIC);
            case 22:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_3, CharacterElements::MYSTIC);
            case 23:
                return CharacterItemEffects::elemental_exp_spell_item_effect(self, CharacterItemRank::ITEM_RANK_A, CharacterElements::MYSTIC);
            case 24:
                return CharacterItemEffects::energy_orb_effect(self, CharacterElements::EARTH);
            case 25:
                return CharacterItemEffects::energy_orb_effect(self, CharacterElements::AIR);
            case 26:
                return CharacterItemEffects::energy_orb_effect(self, CharacterElements::FIRE);
            case 27:
                return CharacterItemEffects::energy_orb_effect(self, CharacterElements::WATER);
            case 28:
                return CharacterItemEffects::energy_orb_effect(self, CharacterElements::MYSTIC);
            case 29:
                return CharacterItemEffects::steel_plate_item_effect(self);
            case 30:
                return CharacterItemEffects::curing_spell_item_effect(self);
            case 31:
                return CharacterItemEffects::healing_spell_item_effect(self, CharacterItemRank::ITEM_RANK_1);
            case 32:
                return CharacterItemEffects::healing_spell_item_effect(self, CharacterItemRank::ITEM_RANK_2);
            case 33:
                return CharacterItemEffects::healing_spell_item_effect(self, CharacterItemRank::ITEM_RANK_3);
            case 34:
                return CharacterItemEffects::healing_spell_item_effect(self, CharacterItemRank::ITEM_RANK_A);
            default:
                // not a valid item or item has no effect
                return false;
            }
        }

        namespace item {
            bool CharacterItemEffects::exp_spell_item_effect(CharacterBattleHandler* self, enum CharacterItemRank item_rank)
            {
                uint16_t raise_exp = 0, level_exp_diff = 0, cur_exp = 0;
                uint8_t cur_level = 0;

                switch (item_rank) {
                case CharacterItemRank::ITEM_RANK_1:
                    cur_level = self->get_base_level();
                    level_exp_diff = Character::calculate_exp_at_level(cur_level + 1) - Character::calculate_exp_at_level(cur_level);
                    raise_exp = (uint16_t)floorf(level_exp_diff * 0.5f);
                    break;
                case CharacterItemRank::ITEM_RANK_2:
                    raise_exp = self->get_base_exp_to_next_level();
                    break;
                case CharacterItemRank::ITEM_RANK_3:
                    cur_level = self->get_base_level();
                    cur_exp = self->get_base_exp();
                    raise_exp = Character::calculate_exp_at_level(cur_level + 2) - cur_exp;
                    break;
                case CharacterItemRank::ITEM_RANK_A:
                    cur_level = self->get_base_level();
                    cur_exp = self->get_base_exp();
                    raise_exp = Character::calculate_exp_at_level(cur_level + 5) - cur_exp;
                    break;
                default:
                    // not a valid rank for this item
                    return false;
                }

                self->base_gain_exp(raise_exp);
                return true;
            }

            bool CharacterItemEffects::elemental_exp_spell_item_effect(CharacterBattleHandler* self, enum CharacterItemRank item_rank, enum CharacterElements item_element)
            {
                if (self->get_passive_ability().native_element != item_element) {
                    return exp_spell_item_effect(self, item_rank);
                }

                uint16_t raise_exp = 0, cur_exp = 0;
                uint8_t cur_level = 0;

                switch (item_rank) {
                case CharacterItemRank::ITEM_RANK_1:
                    raise_exp = self->get_base_exp_to_next_level();
                    break;
                case CharacterItemRank::ITEM_RANK_2:
                    cur_level = self->get_base_level();
                    cur_exp = self->get_base_exp();
                    raise_exp = Character::calculate_exp_at_level(cur_level + 2) - cur_exp;
                    break;
                case CharacterItemRank::ITEM_RANK_3:
                    cur_level = self->get_base_level();
                    cur_exp = self->get_base_exp();
                    raise_exp = Character::calculate_exp_at_level(cur_level + 5) - cur_exp;
                    break;
                case CharacterItemRank::ITEM_RANK_A:
                    cur_level = self->get_base_level();
                    cur_exp = self->get_base_exp();
                    raise_exp = Character::calculate_exp_at_level(cur_level + 10) - cur_exp;
                    break;
                default:
                    // not a valid rank for this item
                    return false;
                }

                self->base_gain_exp(raise_exp);
                return true;
            }

            bool CharacterItemEffects::energy_orb_effect(CharacterBattleHandler* self, enum CharacterElements item_element)
            {
                uint16_t raise_exp = 0;

                if (self->get_passive_ability().native_element == item_element) {
                    raise_exp = 500;
                }
                else {
                    raise_exp = 250;
                }

                self->base_gain_exp(raise_exp);
                return true;
            }

            bool CharacterItemEffects::steel_plate_item_effect(CharacterBattleHandler* self)
            {
                return self->restore_armor();
            }

            bool CharacterItemEffects::curing_spell_item_effect(CharacterBattleHandler* self)
            {
                return self->cure_status();
            }

            bool CharacterItemEffects::healing_spell_item_effect(CharacterBattleHandler* self, enum CharacterItemRank item_rank)
            {
                uint16_t heal_val = 0, max_health = 0;

                switch (item_rank) {
                case CharacterItemRank::ITEM_RANK_1:
                    max_health = self->get_maximum_health();
                    heal_val = std::max((uint16_t)floorf(max_health * 0.2f), (uint16_t)1);
                    break;
                case CharacterItemRank::ITEM_RANK_2:
                    max_health = self->get_maximum_health();
                    heal_val = std::max((uint16_t)floorf(max_health * 0.4f), (uint16_t)1);
                    break;
                case CharacterItemRank::ITEM_RANK_3:
                    max_health = self->get_maximum_health();
                    heal_val = std::max((uint16_t)floorf(max_health * 0.8f), (uint16_t)1);
                    break;
                case CharacterItemRank::ITEM_RANK_A:
                    heal_val = 65535;
                    self->cure_status();
                    break;
                default:
                    // not a valid rank for this item
                    return false;
                }

                self->restore_health(heal_val);
                return true;
            }
        }
    }
}