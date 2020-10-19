/**
 * QuestHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "CharacterBattleHandler.h"
#include "Quest.h"

namespace le_hero {
	namespace quest {
		class QuestHandler
		{
		private:
			std::shared_ptr<Quest> base;

			QuestEnemyInfo current_enemy_info;
			std::shared_ptr<CharacterBattleHandler> current_enemy;
			uint8_t num_enemies_defeated = 0;

			std::shared_ptr<CharacterBattleHandler> player;

			bool quest_started = false;
			bool quest_completed = false;

			void setup_enemy();

			void enemy_defeated();
			void player_defeated();

			bool perform_weapon_action(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
			bool perform_special_action(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);
			bool perform_action(std::shared_ptr<CharacterBattleHandler> self, std::shared_ptr<CharacterBattleHandler> enemy);

		public:
			QuestHandler(std::shared_ptr<Quest> base, std::shared_ptr<CharacterBattleHandler> player);

			bool perform_turn();

			void start_quest();
			void end_quest(bool lose = false);
		};
	}
}