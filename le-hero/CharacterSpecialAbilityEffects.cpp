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
                return false;
            }

            bool CharacterSpecialAbilityEffects::flaming_vortex_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::inferno_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::hurricane_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::whirlpool_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::landslide_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::extinguish_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::scald_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::speedster_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::power_trick_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::platinum_power_play_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::guard_stance_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::honor_amongst_thieves_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::good_samaritan_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }

            bool CharacterSpecialAbilityEffects::call_to_arms_special_effect(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
            {
                return false;
            }
        }
    }
}