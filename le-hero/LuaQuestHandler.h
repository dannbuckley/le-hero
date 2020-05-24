/**
 * LuaQuestHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "LuaIncludes.h"
#include "Quest.h"

namespace le_hero {
	namespace lua {
		class LuaQuestHandler
		{
		private:
			lua_State* L;

			bool parse_quest_enemy_info_objects(quest::Quest& q);
			bool parse_quest_prize_items(quest::Quest& q);
			bool parse_quest_prize_weapons(quest::Quest& q);

		public:
			LuaQuestHandler();

			// Parser for quest data file in quests/ folder
			bool parse_quest_file(std::string quest_file, quest::Quest& q);
		};
	}
}