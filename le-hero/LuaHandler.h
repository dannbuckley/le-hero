/**
 * LuaHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "lua-5_3_5/include/lua.hpp"
#include "CharacterElement.h"
#include "CharacterRank.h"
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

			std::string get_string_value(std::string key);
			lua_Number get_number_value(std::string key);
			bool get_bool_value(std::string key);

			bool parse_elements(std::vector<CharacterElement>& e);
			bool parse_ranks(std::vector<CharacterRank>& r);
			bool parse_statuses(std::vector<CharacterStatus>& s);
			bool parse_weapons(std::vector<CharacterWeapon>& w);
		public:
			LuaHandler();
			bool parse_file(std::string file_name,
				std::vector<CharacterElement>& e,
				std::vector<CharacterRank>& r,
				std::vector<CharacterStatus>& s,
				std::vector<CharacterWeapon>& w);
		};
	}
}

