/**
 * LuaQuestHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <future>
#include <queue>
#include <lua.hpp>
#include "Quest.h"

namespace le_hero {
	namespace lua {
		class LuaQuestHandler
		{
		private:
			typedef struct {
				uint8_t index;
				quest::Quest data;
			} QuestInfo;

			struct QuestInfoCmp {
				bool operator()(const QuestInfo& lhs, const QuestInfo& rhs) const
				{
					return lhs.index > rhs.index;
				}
			};

			static void load_individual_quest(std::priority_queue<QuestInfo,
				std::vector<QuestInfo>,
				QuestInfoCmp>* pq,
				std::pair<std::string, std::string> quest_ref,
				uint8_t index);

			std::priority_queue<QuestInfo, std::vector<QuestInfo>, QuestInfoCmp> construct_quests_queue();

			bool parse_quest_enemy_info_objects(lua_State* L, quest::Quest& q);
			bool parse_quest_prize_items(lua_State* L, quest::Quest& q);
			bool parse_quest_prize_weapons(lua_State* L, quest::Quest& q);

			// Parser for quest data file in quests/ folder
			bool parse_quest_file(std::string quest_file, quest::Quest& q);

		public:
			std::vector<quest::Quest> load_all_quests();
		};
	}
}