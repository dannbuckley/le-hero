/**
 * LuaQuestHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#include "LuaDefaults.h"
#include "LuaQuestHandler.h"
#include "Timer.h"

namespace le_hero {
    namespace lua {
		static std::mutex quests_mutex;

		// Loads an individual quest asynchronously
		void LuaQuestHandler::load_individual_quest(QuestLoaderQueue* pq, std::pair<std::string, std::string> quest_ref, uint8_t index)
		{
			LuaQuestHandler lqh;
			quest::Quest q;
			q.name = quest_ref.second;
			bool parse_result = lqh.parse_quest_file(quest_ref.first, q);

			if (!parse_result) {
				throw exception::unsuccessful_lua_parse_error();
			}

			std::lock_guard<std::mutex> lock(quests_mutex);
			pq->push(q, index);
		}

		// Constructs a priority queue from all quest data with the quest index acting as the item priority
		QuestLoaderQueue LuaQuestHandler::construct_quests_queue()
		{
			QuestLoaderQueue pq;
			std::vector<std::future<void>> quest_futures;
			auto num_quests = game::get_num_quest_refs();

			for (unsigned int i = 0; i < num_quests; i++) {
				const auto& q_ref = game::get_quest_ref(i);
				quest_futures.push_back(std::async(std::launch::async, load_individual_quest, &pq, q_ref, i));
			}

			// wait for all quests to finish loading
			while (pq.size() != num_quests);

			return pq;
		}

		// Parses each Quest enemy info object found in quest file
        bool LuaQuestHandler::parse_quest_enemy_info_objects(lua_State* L, quest::Quest& q)
        {
			size_t num_enemies = 0;
			try {
				num_enemies = (size_t)LuaHelpers::get_number_value_from_table(L, "NumEnemies");
			}
			catch (exception::unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// get EnemyInfo subtable
			lua_pushstring(L, "EnemyInfo");
			lua_gettable(L, -2);

			if (lua_istable(L, -1)) {
				for (unsigned int i = 0; i < num_enemies; i++) {
					// push info object index number onto lua stack
					lua_pushnumber(L, i);
					lua_gettable(L, -2);

					if (lua_istable(L, -1)) {
						// construct CharacterMeta object from lua table
						CharacterMeta meta;

						try {
							meta.element = (CharacterElements)LuaHelpers::get_number_value_from_table(L, "Element");
							meta.rank = (CharacterRanks)LuaHelpers::get_number_value_from_table(L, "Rank");
							meta.total_experience = (uint16_t)LuaHelpers::get_number_value_from_table(L, "TotalExperience");
							meta.weapon_index = (uint8_t)LuaHelpers::get_number_value_from_table(L, "WeaponIndex");
							meta.special_ability_index = (uint8_t)LuaHelpers::get_number_value_from_table(L, "SpecialAbilIndex");
						}
						catch (exception::unexpected_type_error& e) {
							std::cout << e.what() << std::endl;
							return false;
						}

						// push enemy info to Quest object vector
						q.enemy_info.push_back(meta);

						// pop table off lua stack
						lua_pop(L, 1);
					}
				}
			}
			else {
				// EnemyInfo table not found
				return false;
			}

			// pop table off lua stack
			lua_pop(L, 1);

			return true;
        }

		// Parses each Quest prize item found in quest file
        bool LuaQuestHandler::parse_quest_prize_items(lua_State* L, quest::Quest& q)
        {
			size_t num_prize_items = 0;
			try {
				num_prize_items = (size_t)LuaHelpers::get_number_value_from_table(L, "NumPrizeItems");
			}
			catch (exception::unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// get PrizeItems subtable
			lua_pushstring(L, "PrizeItems");
			lua_gettable(L, -2);

			if (lua_istable(L, -1)) {
				for (unsigned int i = 0; i < num_prize_items; i++) {
					// push prize item index number onto lua stack
					lua_pushnumber(L, i);
					lua_gettable(L, -2);

					if (lua_isnumber(L, -1)) {
						// save prize item to Quest object vector
						q.prize_items.push_back((uint8_t)lua_tonumber(L, -1));

						// pop value off lua stack
						lua_pop(L, 1);
					}
					else {
						// value is incorrect type
						return false;
					}
				}
			}
			else {
				// PrizeItems table not found
				return false;
			}

			// pop table off lua stack
			lua_pop(L, 1);

			return true;
        }

		// Parses each Quest prize weapon found in quest file
        bool LuaQuestHandler::parse_quest_prize_weapons(lua_State* L, quest::Quest& q)
        {
			size_t num_prize_weapons = 0;
			try {
				num_prize_weapons = (size_t)LuaHelpers::get_number_value_from_table(L, "NumPrizeWeapons");
			}
			catch (exception::unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// get PrizeWeapons subtable
			lua_pushstring(L, "PrizeWeapons");
			lua_gettable(L, -2);

			if (lua_istable(L, -1)) {
				for (unsigned int i = 0; i < num_prize_weapons; i++) {
					// push prize weapon index number onto lua stack
					lua_pushnumber(L, i);
					lua_gettable(L, -2);

					if (lua_isnumber(L, -1)) {
						// save prize weapon to Quest object vector
						q.prize_weapons.push_back((uint8_t)lua_tonumber(L, -1));

						// pop value off lua stack
						lua_pop(L, 1);
					}
					else {
						// value is incorrect type
						return false;
					}
				}
			}
			else {
				// PrizeWeapons table not found
				return false;
			}

			// pop table off lua stack
			lua_pop(L, 1);

			return true;
        }

		// Parses quest file
        bool LuaQuestHandler::parse_quest_file(std::string quest_file, quest::Quest& q)
        {
			auto L = luaL_newstate(); // initialize lua stack
			luaL_openlibs(L); // enable lua standard libraries

			// ensure integrity of quest file
			if (!LuaHelpers::validate_lua(L, luaL_dofile(L, quest_file.c_str()))) {
				return false;
			}

			// parse quest data
			try {
				lua_getglobal(L, "GetQuest");
				if (lua_isfunction(L, -1)) {
					if (LuaHelpers::validate_lua(L, lua_pcall(L, 0, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Quest from lua table
							q.description = LuaHelpers::get_string_value_from_table(L, "Description");
							q.recommended_level = (uint8_t)LuaHelpers::get_number_value_from_table(L, "RecommendedLevel");
							q.quest_terrain = (CharacterElements)LuaHelpers::get_number_value_from_table(L, "QuestTerrain");
							q.prize_coins = (uint32_t)LuaHelpers::get_number_value_from_table(L, "PrizeCoins");
							q.prize_experience = (uint16_t)LuaHelpers::get_number_value_from_table(L, "PrizeExp");

							if (!parse_quest_enemy_info_objects(L, q)) {
								return false;
							}

							if (!parse_quest_prize_items(L, q)) {
								return false;
							}

							if (!parse_quest_prize_weapons(L, q)) {
								return false;
							}

							// pop table off lua stack
							lua_pop(L, 1);
						}
					}
				}
			}
			catch (exception::unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// close lua state
			lua_close(L);
			return true;
        }

		// Loads data for all quests found in game environment quest references
		std::vector<quest::Quest> LuaQuestHandler::load_all_quests()
		{
			PROFILE_TIMER(); // record the time elapsed for debugging
			auto pq = construct_quests_queue();
			return pq.export_to_vector();
		}
    }
}