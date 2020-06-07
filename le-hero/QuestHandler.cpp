/**
 * QuestHandler.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <cmath>
#include "CharacterEffectFunctions.h"
#include "QuestHandler.h"

namespace le_hero {
	namespace quest {
        void QuestHandler::distribute_prizes()
        {
            this->player->obtain_quest_prizes(this->base->prize_coins,
                this->base->prize_experience,
                this->base->prize_items,
                this->base->prize_weapons);
        }

        void QuestHandler::setup_enemy()
        {
            if (this->num_enemies_defeated == this->base->enemy_info.size()) {
                this->end_quest();
            }
            else {
                this->current_enemy_info = QuestEnemyInfo{ this->num_enemies_defeated, this->base->enemy_info[this->num_enemies_defeated] };

                // TODO: test this method of constructing next enemy Battle Handler
                std::shared_ptr<Character> enemy_base = std::make_shared<Character>(this->current_enemy_info.enemy_meta);
                this->current_enemy = std::make_shared<CharacterBattleHandler>(enemy_base);
                this->current_enemy->register_battle(this->base->quest_terrain);
            }
        }

        void QuestHandler::enemy_defeated()
        {
            game::game_act(StateActions::QUEST_FINISH_PERFORM_ACTIONS);

            ++this->num_enemies_defeated;
            this->setup_enemy();

            if (!this->quest_completed) {
                this->player->new_turn();
                game::game_act(StateActions::QUEST_START_TURN);
            }
        }

        void QuestHandler::player_defeated()
        {
            // "You lose!"
            game::game_act(StateActions::QUEST_FINISH_PERFORM_ACTIONS);
            this->end_quest(true);
        }

        bool QuestHandler::perform_weapon_action(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
        {
            auto equipped_weapon = self->get_equipped_weapon();
            uint8_t wpn_strength = equipped_weapon.strength;
            auto p_abil = self->get_passive_ability();
            if (equipped_weapon.element == p_abil.native_element) {
                wpn_strength += 20; // same-element bonus damage
            }
            uint16_t damage = (uint16_t)floorf((self->calculate_battle_attack_stat() * (wpn_strength / 100.0f)) + 3.0f);

            uint16_t eh_before = enemy->get_current_health();
            uint16_t eh_after = enemy->damage_health(damage);
            self->register_damage_dealt(eh_before - eh_after);

            if (equipped_weapon.can_inflict_status) {
                enemy->inflict_status(equipped_weapon.inflicted_status);
            }

            return true;
        }

        bool QuestHandler::perform_special_action(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
        {
            return effect::activate_special_ability_effect(self, enemy);
        }

        bool QuestHandler::perform_action(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy)
        {
            bool result = false;
            auto selected_action = self->get_selected_action();

            switch (selected_action) {
            case CharacterActionTypes::PASS:
                result = true;
                break;
            case CharacterActionTypes::WEAPON:
                result = this->perform_weapon_action(self, enemy);
                break;
            case CharacterActionTypes::SPECIAL_ABILITY:
                result = this->perform_special_action(self, enemy);
                break;
            default:
                // not a valid action
                break;
            }

            self->reset_turn_data();

            return result;
        }

        QuestHandler::QuestHandler(std::shared_ptr<Quest> base, std::shared_ptr<CharacterBattleHandler> player):
            base(base), 
            player(player)
        {
        }

        bool QuestHandler::perform_turn()
        {
            if (game::get_current_state() != StateTypes::QUEST_READY_FOR_TURN) {
                // cannot perform the turn until both Characters are ready
                return false;
            }

            game::game_act(StateActions::QUEST_START_PERFORM_ACTIONS);

            // activate passive abilities
            effect::activate_passive_ability_effect(this->player);
            effect::activate_passive_ability_effect(this->current_enemy);

            uint16_t player_current_speed = this->player->calculate_battle_speed_stat();
            uint16_t enemy_current_speed = this->current_enemy->calculate_battle_speed_stat();

            if (player_current_speed >= enemy_current_speed) {
                // player is faster than / as fast as the enemy
                this->perform_action(this->player, this->current_enemy);
                if (this->current_enemy->get_current_health() == 0) {
                    // player defeats the enemy
                    this->enemy_defeated();
                    return true;
                }

                this->perform_action(this->current_enemy, this->player);
                if (this->player->get_current_health() == 0) {
                    // enemy defeats the player
                    this->player_defeated();
                    return true;
                }
            }
            else {
                // player is slower than the enemy
                this->perform_action(this->current_enemy, this->player);
                if (this->player->get_current_health() == 0) {
                    // enemy defeats the player
                    this->player_defeated();
                    return true;
                }

                this->perform_action(this->player, this->current_enemy);
                if (this->current_enemy->get_current_health() == 0) {
                    // player defeats the enemy
                    this->enemy_defeated();
                    return true;
                }
            }

            game::game_act(StateActions::QUEST_FINISH_PERFORM_ACTIONS);

            this->player->new_turn();
            this->current_enemy->new_turn();

            game::game_act(StateActions::QUEST_START_TURN);

            return true;
        }

        void QuestHandler::start_quest()
        {
            game::game_act(StateActions::START_QUEST);
            this->player->register_battle(this->base->quest_terrain);
            this->setup_enemy();
        }

        void QuestHandler::end_quest(bool lose)
        {
            if (!lose) {
                this->quest_completed = true;
                this->distribute_prizes();
            }

            this->player->end_battle();
            game::game_act(StateActions::END_QUEST);
        }
    }
}