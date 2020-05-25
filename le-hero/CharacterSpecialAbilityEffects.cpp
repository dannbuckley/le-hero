/**
 * CharacterSpecialAbilityEffects.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <algorithm>
#include <cmath>
#include "CharacterSpecialAbilityEffects.h"

namespace le_hero {
    namespace effect {
        bool activate_special_ability_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
        {
            using namespace special_ability;

            auto s_abil = self->get_special_ability();

            switch (s_abil.index) {
            case 0:
                return CharacterSpecialAbilityEffects::protect_special_effect(self, enemy);
            case 1:
                return CharacterSpecialAbilityEffects::recovery_special_effect(self, enemy);
            case 2:
                return CharacterSpecialAbilityEffects::tricky_mirror_special_effect(self, enemy);
            case 3:
                return CharacterSpecialAbilityEffects::revenge_special_effect(self, enemy);
            case 4:
                return CharacterSpecialAbilityEffects::deadly_accuracy_special_effect(self, enemy);
            case 5:
                return CharacterSpecialAbilityEffects::flaming_vortex_special_effect(self, enemy);
            case 6:
                return CharacterSpecialAbilityEffects::inferno_special_effect(self, enemy);
            case 7:
                return CharacterSpecialAbilityEffects::hurricane_special_effect(self, enemy);
            case 8:
                return CharacterSpecialAbilityEffects::whirlpool_special_effect(self, enemy);
            case 9:
                return CharacterSpecialAbilityEffects::landslide_special_effect(self, enemy);
            case 10:
                return CharacterSpecialAbilityEffects::extinguish_special_effect(self, enemy);
            case 11:
                return CharacterSpecialAbilityEffects::scald_special_effect(self, enemy);
            case 12:
                return CharacterSpecialAbilityEffects::speedster_special_effect(self, enemy);
            case 13:
                return CharacterSpecialAbilityEffects::power_trick_special_effect(self, enemy);
            case 14:
                return CharacterSpecialAbilityEffects::platinum_power_play_special_effect(self, enemy);
            case 15:
                return CharacterSpecialAbilityEffects::guard_stance_special_effect(self, enemy);
            case 16:
                return CharacterSpecialAbilityEffects::honor_amongst_thieves_special_effect(self, enemy);
            case 17:
                return CharacterSpecialAbilityEffects::good_samaritan_special_effect(self, enemy);
            case 18:
                return CharacterSpecialAbilityEffects::call_to_arms_special_effect(self, enemy);
            default:
                // not a valid special ability
                return false;
            }
        }

        namespace special_ability {
            bool CharacterSpecialAbilityEffects::protect_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                // self-inflict Protecting status
                return self->inflict_status(12);
            }

            bool CharacterSpecialAbilityEffects::recovery_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                // restore 25% of maximum health
                uint16_t max_health = self->get_maximum_health();
                uint16_t heal_val = (uint16_t)floorf(max_health * 0.25f);
                self->restore_health(heal_val);

                // self-inflict Amnesiac status
                self->inflict_status(9);
                return true;
            }

            bool CharacterSpecialAbilityEffects::tricky_mirror_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint8_t self_stl = self->get_status_turns_left();
                if (self_stl > 0) {
                    // if self is inflicted with status, transfer to enemy
                    auto self_status = self->get_inflicted_status();
                    bool transfer = enemy->inflict_status(self_status);
                    if (transfer) {
                        // cure own status if transfer is successful
                        self->cure_status();
                        return true;
                    }
                }

                // return false if ability has no effect
                return false;
            }

            bool CharacterSpecialAbilityEffects::revenge_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t max_health = self->get_maximum_health();
                uint16_t cur_health = self->get_current_health();
                uint16_t damage = std::max(max_health - cur_health, 1); // damage >= 1
                enemy->damage_health(damage);
                return true;
            }

            bool CharacterSpecialAbilityEffects::deadly_accuracy_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.75f), (uint16_t)1);
                if (self->get_equipped_weapon().range == WeaponRange::LONG) {
                    damage *= 2;
                }
                enemy->damage_health(damage);
                return false;
            }

            bool CharacterSpecialAbilityEffects::flaming_vortex_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.75f), (uint16_t)1);
                enemy->damage_health(damage);

                // inflict enemy with Burn status
                enemy->inflict_status(0);
                return false;
            }

            bool CharacterSpecialAbilityEffects::inferno_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.5f), (uint16_t)1);
                enemy->damage_health(damage, true);
                return true;
            }

            bool CharacterSpecialAbilityEffects::hurricane_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.75f), (uint16_t)1);
                enemy->damage_health(damage);

                // inflict enemy with Weightless status
                enemy->inflict_status(6);
                return true;
            }

            bool CharacterSpecialAbilityEffects::whirlpool_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.75f), (uint16_t)1);
                enemy->damage_health(damage, true);
                return true;
            }

            bool CharacterSpecialAbilityEffects::landslide_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.75f), (uint16_t)1);
                enemy->damage_health(damage, true);
                return true;
            }

            bool CharacterSpecialAbilityEffects::extinguish_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.25f), (uint16_t)1);
                if (self->get_passive_ability().native_element == CharacterElements::FIRE) {
                    damage *= 2;
                }
                enemy->damage_health(damage);
                return true;
            }

            bool CharacterSpecialAbilityEffects::scald_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.5f), (uint16_t)1);
                enemy->damage_health(damage);

                // inflict enemy with Burn status
                enemy->inflict_status(0);
                return true;
            }

            bool CharacterSpecialAbilityEffects::speedster_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t cur_speed = self->calculate_battle_speed_stat();
                uint16_t base_speed = self->get_base_speed_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * (float)(cur_speed / base_speed)), (uint16_t)1);
                enemy->damage_health(damage);
                return true;
            }

            bool CharacterSpecialAbilityEffects::power_trick_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_enemy_attack = enemy->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_enemy_attack * 0.75f), (uint16_t)1);
                enemy->damage_health(damage);
                return true;
            }

            bool CharacterSpecialAbilityEffects::platinum_power_play_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t cur_attack = self->calculate_battle_attack_stat();
                uint16_t damage = std::max((uint16_t)floorf(cur_attack * 0.75f), (uint16_t)1);
                if (self->get_equipped_weapon().range == WeaponRange::MELEE) {
                    damage *= 2;
                }
                enemy->damage_health(damage);
                return true;
            }

            bool CharacterSpecialAbilityEffects::guard_stance_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                if (self->get_inflicted_status().index != 3) {
                    // if the character is not inflicted with Guarding,
                    // cure current status and self-inflict Guarding
                    self->cure_status();
                    self->inflict_status(3);
                    return true;
                }

                // return false if ability had no effect
                return false;
            }

            bool CharacterSpecialAbilityEffects::honor_amongst_thieves_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                uint16_t self_max_health = self->get_maximum_health();
                uint16_t enemy_max_health = enemy->get_maximum_health();

                if (self->get_passive_ability().native_element == enemy->get_passive_ability().native_element) {
                    self->restore_health((uint16_t)ceilf(self_max_health * 0.1f));
                    enemy->restore_health((uint16_t)ceilf(enemy_max_health * 0.1f));
                }
                else {
                    self->restore_health((uint16_t)ceilf(enemy_max_health * 0.1f));
                    enemy->damage_health((uint16_t)ceilf(enemy_max_health * 0.1f), true);
                }

                return true;
            }

            bool CharacterSpecialAbilityEffects::good_samaritan_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return enemy->cure_status();
            }

            bool CharacterSpecialAbilityEffects::call_to_arms_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                // get data for Frenzy status
                auto env = self->get_base_environment();
                auto frenzy_data = env->get_status(13);

                // calculate status effect length
                uint8_t length = (uint8_t)ceilf((self->get_equipped_weapon().strength / 100.0f) + 1.0f);
                frenzy_data.effect_length = length;

                // self-inflict Frenzy status with custom length
                return self->inflict_status(frenzy_data);
            }
        }
    }
}