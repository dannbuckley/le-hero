/**
 * LuaHandler.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <iostream>
#include "LuaHandler.h"

namespace le_hero {
	namespace lua {
		// Validates a given lua response value
		bool LuaHandler::validate_lua(int r)
		{
			if (r != LUA_OK) {
				std::string err = lua_tostring(L, -1);
				std::cout << err << std::endl;
				return false;
			}
			return true;
		}

		// Retrieves string-type value with associated key from lua table
		std::string LuaHandler::get_string_value(std::string key)
		{
			lua_pushstring(L, key.c_str());
			lua_gettable(L, -2);
			std::string value = lua_tostring(L, -1);
			lua_pop(L, 1);
			return value;
		}

		// Retrieves number-type value with associated key from lua table
		lua_Number LuaHandler::get_number_value(std::string key)
		{
			lua_pushstring(L, key.c_str());
			lua_gettable(L, -2);
			lua_Number value = lua_tonumber(L, -1);
			lua_pop(L, 1);
			return value;
		}

		// Retrieves bool-type value with associated key from lua table
		bool LuaHandler::get_bool_value(std::string key)
		{
			lua_pushstring(L, key.c_str());
			lua_gettable(L, -2);
			bool value = lua_toboolean(L, -1);
			lua_pop(L, 1);
			return value;
		}

		// Parses each Element object found in settings file
		bool LuaHandler::parse_elements(std::vector<CharacterElement>& e)
		{
			// use lua GetElement function to retrieve each individual Element object
			for (int i = 0; i <= (int)CharacterElements::ALPHA; i++) {
				lua_getglobal(L, "GetElement");
				if (lua_isfunction(L, -1)) {
					lua_pushnumber(L, i);
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Element object from lua table
							CharacterElement element;
							element.name = get_string_value("Name");
							element.armor_percent = (uint8_t)get_number_value("ArmorPercent");
							element.armor_turns = (uint8_t)get_number_value("ArmorTurns");
							element.base_attack = (uint8_t)get_number_value("BaseAttack");
							element.base_speed = (uint8_t)get_number_value("BaseSpeed");
							element.base_health = (uint8_t)get_number_value("BaseHealth");

							// push Element object to game environment vector
							e.push_back(element);
							lua_pop(L, 1);
						}
					}
				}
			}

			return true;
		}

		// Parses each Rank object found in settings file
		bool LuaHandler::parse_ranks(std::vector<CharacterRank>& r)
		{
			// use lua GetRank function to retrieve each individual Rank object
			for (int i = 0; i <= (int)CharacterRanks::Z; i++) {
				lua_getglobal(L, "GetRank");
				if (lua_isfunction(L, -1)) {
					// push object index number
					lua_pushnumber(L, i);

					// call GetRank(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Rank object from lua table
							CharacterRank rank;
							rank.name = get_string_value("Name");
							rank.attack_boost = (uint8_t)get_number_value("AttackBoost");
							rank.speed_boost = (uint8_t)get_number_value("SpeedBoost");
							rank.health_boost = (uint8_t)get_number_value("HealthBoost");

							// push Rank object to game environment vector
							r.push_back(rank);
							lua_pop(L, 1);
						}
					}
				}
			}

			return true;
		}

		// Parses each Status object found in settings file
		bool LuaHandler::parse_statuses(std::vector<CharacterStatus>& s)
		{
			lua_getglobal(L, "num_statuses");
			if (!lua_isnumber(L, -1)) {
				return false;
			}
			int num_statuses = (int)lua_tonumber(L, -1);
			lua_pop(L, 1);

			// use lua GetStatus function to retrieve each individual Status object
			for (int i = 0; i < num_statuses; i++) {
				lua_getglobal(L, "GetStatus");
				if (lua_isfunction(L, -1)) {
					// push object index number
					lua_pushnumber(L, i);

					// call GetStatus(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Status object from lua table
							CharacterStatus status;
							status.name = get_string_value("Name");
							status.effect = get_string_value("Effect");
							status.effect_length = (uint8_t)get_number_value("EffectLength");
							status.status_type = (CharacterStatusTypes)get_number_value("StatusType");

							// push Status object to game environment vector
							s.push_back(status);
							lua_pop(L, 1);
						}
					}
				}
			}

			return true;
		}

		// Parses each Weapon object found in settings file
		bool LuaHandler::parse_weapons(std::vector<CharacterWeapon>& w)
		{
			lua_getglobal(L, "num_weapons");
			if (!lua_isnumber(L, -1)) {
				return false;
			}
			int num_weapons = (int)lua_tonumber(L, -1);
			lua_pop(L, 1);

			// use lua GetWeapon function to retrieve each individual Weapon object
			for (int i = 0; i < num_weapons; i++) {
				lua_getglobal(L, "GetWeapon");
				if (lua_isfunction(L, -1)) {
					// push object index number
					lua_pushnumber(L, i);

					// call GetWeapon(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Weapon object from lua table
							CharacterWeapon weapon;
							weapon.collection_index = (uint8_t)get_number_value("CollectionIndex");
							weapon.category = (WeaponCategory)get_number_value("Category");
							weapon.handling = (WeaponHandling)get_number_value("Handling");
							weapon.weight = (WeaponWeight)get_number_value("Weight");
							weapon.range = (WeaponRange)get_number_value("Range");
							weapon.damage_type = (WeaponDamageType)get_number_value("DamageType");
							weapon.name = get_string_value("Name");
							weapon.element = (CharacterElements)get_number_value("Element");
							weapon.strength = (uint8_t)get_number_value("Strength");
							weapon.can_inflict_status = get_bool_value("CanInflictStatus");

							if (weapon.can_inflict_status) {
								weapon.inflicted_status = (uint8_t)get_number_value("InflictedStatus");
							}
							else {
								weapon.inflicted_status = 0;
							}

							// push Weapon object to game environment vector
							w.push_back(weapon);
							lua_pop(L, 1);
						}
					}
				}
			}

			return true;
		}

		// Default constructor
		LuaHandler::LuaHandler()
		{
			L = luaL_newstate(); // initialize lua stack
			luaL_openlibs(L); // enable lua standard libraries
		}

		// Parses settings file for game environment
		bool LuaHandler::parse_file(std::string file_name, std::vector<CharacterElement>& e, std::vector<CharacterRank>& r, std::vector<CharacterStatus>& s, std::vector<CharacterWeapon>& w)
		{
			// ensure integrity of settings file
			if (!validate_lua(luaL_dofile(L, file_name.c_str()))) {
				return false;
			}

			// parse game data from settings file
			parse_elements(e);
			parse_ranks(r);
			parse_statuses(s);
			parse_weapons(w);
			return true;
		}
	}
}
