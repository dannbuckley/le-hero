/**
 * LuaDefaults.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <iostream>
#include <exception>
#include <string>
#include "GameExceptions.h"
#include "LuaIncludes.h"
#include "spdlog/spdlog.h"

namespace le_hero {
	namespace lua {
		class LuaHelpers {
		public:
			// Validates a given lua response value
			static bool validate_lua(lua_State* L, int r)
			{
				if (r != LUA_OK) {
					std::string err = lua_tostring(L, -1);
					std::cout << err << std::endl;
					return false;
				}
				return true;
			}

			// Retrieves string-type value of global variable var_name from lua file
			static const char* get_global_string_variable(lua_State* L, const char* var_name)
			{
				// get global variable var_name
				lua_getglobal(L, var_name);

				// check for valid type
				if (!lua_isstring(L, -1)) {
					// throw exception for unexpected type
					spdlog::get("logger")->error("Unexpected type for Lua global variable in call LuaHelpers::get_global_string_variable({})", var_name);
					throw exception::unexpected_type_error();
				}

				// convert value to string
				auto var_value = lua_tostring(L, -1);

				// pop value off lua stack
				lua_pop(L, 1);
				return var_value;
			}

			// Retrieves number-type value of global variable var_name from lua file
			static lua_Number get_global_number_variable(lua_State* L, const char* var_name)
			{
				// get global variable var_name
				lua_getglobal(L, var_name);

				// check for valid type
				if (!lua_isnumber(L, -1)) {
					// throw exception for unexpected type
					spdlog::get("logger")->error("Unexpected type for Lua global variable in call LuaHelpers::get_global_number_variable({})", var_name);
					throw exception::unexpected_type_error();
				}

				// convert value to number
				auto var_value = lua_tonumber(L, -1);

				// pop value off lua stack
				lua_pop(L, 1);
				return var_value;
			}

			// Retrieves string-type value with associated key from lua table
			static const char* get_string_value_from_table(lua_State* L, const char* key)
			{
				// push key onto stack and retrieve value from table
				lua_pushstring(L, key);
				lua_gettable(L, -2);

				// check for valid type
				if (!lua_isstring(L, -1)) {
					// throw exception for unexpected type
					spdlog::get("logger")->error("Unexpected type for Lua table value in call LuaHelpers::get_string_value_from_table({})", key);
					throw exception::unexpected_type_error();
				}

				// convert value to string
				auto value = lua_tostring(L, -1);

				// pop value off lua stack
				lua_pop(L, 1);
				return value;
			}

			// Retrieves number-type value with associated key from lua table
			static lua_Number get_number_value_from_table(lua_State* L, const char* key)
			{
				// push key onto stack and retrieve value from table
				lua_pushstring(L, key);
				lua_gettable(L, -2);

				// check for valid type
				if (!lua_isnumber(L, -1)) {
					// throw exception for unexpected type
					spdlog::get("logger")->error("Unexpected type for Lua table value in call LuaHelpers::get_number_value_from_table({})", key);
					throw exception::unexpected_type_error();
				}

				// convert value to number
				auto value = lua_tonumber(L, -1);

				// pop value off lua stack
				lua_pop(L, 1);
				return value;
			}

			// Retrieves bool-type value with associated key from lua table
			static bool get_bool_value_from_table(lua_State* L, const char* key)
			{
				// push key onto stack and retrieve value from table
				lua_pushstring(L, key);
				lua_gettable(L, -2);

				// check for valid type
				if (!lua_isboolean(L, -1)) {
					// throw exception for unexpected type
					spdlog::get("logger")->error("Unexpected type for Lua table value in call LuaHelpers::get_bool_value_from_table({})", key);
					throw exception::unexpected_type_error();
				}

				// convert value to boolean
				bool value = lua_toboolean(L, -1);

				// pop value off lua stack
				lua_pop(L, 1);
				return value;
			}
		};
	}
}