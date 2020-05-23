/**
 * LuaHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include "lua-5_3_5/include/lua.hpp"
#include "CharacterElement.h"
#include "CharacterItem.h"
#include "CharacterPassiveAbility.h"
#include "CharacterRank.h"
#include "CharacterSpecialAbility.h"
#include "CharacterStatus.h"
#include "CharacterWeapon.h"

#ifdef _WIN32
#pragma comment(lib, "lua-5_3_5/liblua53.a")
#endif

namespace le_hero {
	namespace lua {
		class LuaHandler
		{
		private:
			lua_State* L;

			bool validate_lua(int r);

			std::string get_global_string_variable(std::string var_name);
			lua_Number get_global_number_variable(std::string var_name);

			std::string get_string_value_from_table(std::string key);
			lua_Number get_number_value_from_table(std::string key);
			bool get_bool_value_from_table(std::string key);

			/* Object Parsers for Base Settings File */

			bool parse_elements(std::vector<CharacterElement>& e);
			bool parse_ranks(std::vector<CharacterRank>& r);
			bool parse_statuses(std::vector<CharacterStatus>& s);
			bool parse_weapons(std::vector<CharacterWeapon>& w);
			bool parse_passive_abilities(std::vector<CharacterPassiveAbility>& p_abil);
			bool parse_special_abilities(std::vector<CharacterSpecialAbility>& s_abil);
			bool parse_items(std::vector<CharacterItem>& im);

			/* Object Parser for Quests Index File */

			bool parse_quest_references(std::vector<std::pair<std::string, std::string>>& qr);

		public:
			LuaHandler();

			// Parser for base.lua
			bool parse_settings_file(std::string file_name,
				std::string& quests_index_file,
				std::vector<CharacterElement>& e,
				std::vector<CharacterRank>& r,
				std::vector<CharacterStatus>& s,
				std::vector<CharacterWeapon>& w,
				std::vector<CharacterPassiveAbility>& p_abil,
				std::vector<CharacterSpecialAbility>& s_abil,
				std::vector<CharacterItem>& im);

			// Parser for quests/index.lua
			bool parse_quests_index_file(std::string quests_index_file,
				std::vector<std::pair<std::string, std::string>>& qr);

			// Parser for quest data file in quests/ folder
			bool parse_quest_file(std::string quest_file);
		};
	}
}

