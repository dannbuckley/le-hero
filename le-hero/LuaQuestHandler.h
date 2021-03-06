/**
 * LuaQuestHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <lua.hpp>
#include "QuestLoaderQueue.h"

namespace le_hero {
	namespace lua {
		class LuaQuestHandler
		{
		private:
			static void load_individual_quest(QuestLoaderQueue* pq,
				std::pair<std::string, std::string> quest_ref,
				uint8_t index);
			QuestLoaderQueue construct_quests_queue();

			bool parse_quest_enemy_info_objects(lua_State* L, quest::Quest& q);

			// Parser for quest data file in quests/ folder
			bool parse_quest_file(std::string quest_file, quest::Quest& q);

		public:
			std::vector<quest::Quest> load_all_quests();
		};
	}
}