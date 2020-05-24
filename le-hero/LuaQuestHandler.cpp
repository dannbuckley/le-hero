/**
 * LuaQuestHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#include "LuaDefaults.h"
#include "LuaQuestHandler.h"

namespace le_hero {
    namespace lua {
		// Parses each Quest enemy info object found in quest file
        bool LuaQuestHandler::parse_quest_enemy_info_objects(quest::Quest& q)
        {
			int num_enemies = 0;
			try {
				num_enemies = (int)LuaHelpers::get_number_value_from_table(L, "NumEnemies");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// get EnemyInfo subtable
			lua_pushstring(L, "EnemyInfo");
			lua_gettable(L, -2);

			if (lua_istable(L, -1)) {
				for (int i = 0; i < num_enemies; i++) {
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
						catch (unexpected_type_error& e) {
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
        bool LuaQuestHandler::parse_quest_prize_items(quest::Quest& q)
        {
			int num_prize_items = 0;
			try {
				num_prize_items = (int)LuaHelpers::get_number_value_from_table(L, "NumPrizeItems");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// get PrizeItems subtable
			lua_pushstring(L, "PrizeItems");
			lua_gettable(L, -2);

			if (lua_istable(L, -1)) {
				for (int i = 0; i < num_prize_items; i++) {
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
        bool LuaQuestHandler::parse_quest_prize_weapons(quest::Quest& q)
        {
			int num_prize_weapons = 0;
			try {
				num_prize_weapons = (int)LuaHelpers::get_number_value_from_table(L, "NumPrizeWeapons");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// get PrizeWeapons subtable
			lua_pushstring(L, "PrizeWeapons");
			lua_gettable(L, -2);

			if (lua_istable(L, -1)) {
				for (int i = 0; i < num_prize_weapons; i++) {
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

        LuaQuestHandler::LuaQuestHandler() : L(nullptr)
        {
        }

		// Parses quest file
        bool LuaQuestHandler::parse_quest_file(std::string quest_file, quest::Quest& q)
        {
			L = luaL_newstate(); // initialize lua stack
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
							q.description = LuaHelpers::get_string_value_from_table(L, "Description");
							q.recommended_level = (uint8_t)LuaHelpers::get_number_value_from_table(L, "RecommendedLevel");
							q.quest_terrain = (CharacterElements)LuaHelpers::get_number_value_from_table(L, "QuestTerrain");
							q.prize_coins = (uint32_t)LuaHelpers::get_number_value_from_table(L, "PrizeCoins");
							q.prize_experience = (uint16_t)LuaHelpers::get_number_value_from_table(L, "PrizeExp");

							// NumEnemies
							// EnemyInfo -> Element, Rank, TotalExperience, WeaponIndex, SpecialAbilityIndex
							if (!parse_quest_enemy_info_objects(q)) {
								return false;
							}

							if (!parse_quest_prize_items(q)) {
								return false;
							}

							if (!parse_quest_prize_weapons(q)) {
								return false;
							}

							// pop table off lua stack
							lua_pop(L, 1);
						}
					}
				}
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// close lua state
			lua_close(L);
			return true;
        }
    }
}