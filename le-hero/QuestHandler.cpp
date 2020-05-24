/**
 * QuestHandler.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

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
                std::shared_ptr<Character> enemy_base = std::make_shared<Character>(this->env, this->current_enemy_info.enemy_meta);
                this->current_enemy = std::make_shared<CharacterBattleHandler>(enemy_base);
                this->current_enemy->register_battle(this->base->quest_terrain);
            }
        }

        void QuestHandler::enemy_defeated()
        {
            this->env->act(state::StateActions::QUEST_FINISH_PERFORM_ACTIONS);

            ++this->num_enemies_defeated;
            this->setup_enemy();

            if (!this->quest_completed) {
                this->player->new_turn();
                this->env->act(state::StateActions::QUEST_START_TURN);
            }
        }

        void QuestHandler::player_defeated()
        {
            // "You lose!"
            this->env->act(state::StateActions::QUEST_FINISH_PERFORM_ACTIONS);
            this->end_quest(true);
        }

        QuestHandler::QuestHandler(std::shared_ptr<Game> env,
            std::shared_ptr<Quest> base,
            std::shared_ptr<CharacterBattleHandler> player):
            env(env), 
            base(base), 
            player(player)
        {
        }

        bool QuestHandler::perform_turn()
        {
            if (this->env->get_current_state() != state::StateTypes::QUEST_READY_FOR_TURN) {
                // cannot perform the turn until both Characters are ready
                return false;
            }

            this->env->act(state::StateActions::QUEST_START_PERFORM_ACTIONS);

            // TODO: activate player passive ability
            // TODO: activate enemy passive ability

            uint16_t player_current_speed = this->player->calculate_battle_speed_stat();
            uint16_t enemy_current_speed = this->current_enemy->calculate_battle_speed_stat();

            if (player_current_speed >= enemy_current_speed) {
                // player is faster than / as fast as the enemy
                this->player->perform_action(this->current_enemy);
                if (this->current_enemy->get_current_health() == 0) {
                    // player defeats the enemy
                    this->enemy_defeated();
                    return true;
                }

                this->current_enemy->perform_action(this->player);
                if (this->player->get_current_health() == 0) {
                    // enemy defeats the player
                    this->player_defeated();
                    return true;
                }
            }
            else {
                // player is slower than the enemy
                this->current_enemy->perform_action(this->player);
                if (this->player->get_current_health() == 0) {
                    // enemy defeats the player
                    this->player_defeated();
                    return true;
                }

                this->player->perform_action(this->player);
                if (this->current_enemy->get_current_health() == 0) {
                    // player defeats the enemy
                    this->enemy_defeated();
                    return true;
                }
            }

            this->env->act(state::StateActions::QUEST_FINISH_PERFORM_ACTIONS);

            this->player->new_turn();
            this->current_enemy->new_turn();

            this->env->act(state::StateActions::QUEST_START_TURN);

            return true;
        }

        void QuestHandler::start_quest()
        {
            this->env->act(state::StateActions::START_QUEST);
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
            this->env->act(state::StateActions::END_QUEST);
        }
    }
}