/**
 * LuaHandler.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <bitset>
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

		// Retrieves number-type value of global variable var_name from lua file
		lua_Number LuaHandler::get_global_number_variable(std::string var_name)
		{
			// get global variable var_name (assumes var_name exists and is a number)
			lua_getglobal(L, var_name.c_str());
			int var_value = lua_tonumber(L, -1);

			// TODO: throw exception for unexpected type

			// pop value off lua stack
			lua_pop(L, 1);
			return var_value;
		}

		// Retrieves string-type value with associated key from lua table
		std::string LuaHandler::get_string_value_from_table(std::string key)
		{
			// push key onto stack and retrieve value from table
			lua_pushstring(L, key.c_str());
			lua_gettable(L, -2);

			// TODO: throw exception for unexpected type

			// convert value to string
			std::string value = lua_tostring(L, -1);

			// pop value off lua stack
			lua_pop(L, 1);
			return value;
		}

		// Retrieves number-type value with associated key from lua table
		lua_Number LuaHandler::get_number_value_from_table(std::string key)
		{
			// push key onto stack and retrieve value from table
			lua_pushstring(L, key.c_str());
			lua_gettable(L, -2);

			// TODO: throw exception for unexpected type

			// convert value to number
			lua_Number value = lua_tonumber(L, -1);

			// pop value off lua stack
			lua_pop(L, 1);
			return value;
		}

		// Retrieves bool-type value with associated key from lua table
		bool LuaHandler::get_bool_value_from_table(std::string key)
		{
			// push key onto stack and retrieve value from table
			lua_pushstring(L, key.c_str());
			lua_gettable(L, -2);

			// TODO: throw exception for unexpected type

			// convert value to boolean
			bool value = lua_toboolean(L, -1);

			// pop value off lua stack
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
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetElement(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Element object from lua table
							CharacterElement element;
							element.name = get_string_value_from_table("Name");
							element.armor_percent = (uint8_t)get_number_value_from_table("ArmorPercent");
							element.armor_turns = (uint8_t)get_number_value_from_table("ArmorTurns");
							element.base_attack = (uint8_t)get_number_value_from_table("BaseAttack");
							element.base_speed = (uint8_t)get_number_value_from_table("BaseSpeed");
							element.base_health = (uint8_t)get_number_value_from_table("BaseHealth");
							element.element_identifier = (CharacterElements)i;

							// push Element object to game environment vector
							e.push_back(element);

							// pop table off lua stack
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
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetRank(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Rank object from lua table
							CharacterRank rank;
							rank.name = get_string_value_from_table("Name");
							rank.attack_boost = (uint8_t)get_number_value_from_table("AttackBoost");
							rank.speed_boost = (uint8_t)get_number_value_from_table("SpeedBoost");
							rank.health_boost = (uint8_t)get_number_value_from_table("HealthBoost");

							// push Rank object to game environment vector
							r.push_back(rank);

							// pop table off lua stack
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
			// get number of Statuses from global lua variable
			int num_statuses = (int)get_global_number_variable("num_statuses");

			// use lua GetStatus function to retrieve each individual Status object
			for (int i = 0; i < num_statuses; i++) {
				lua_getglobal(L, "GetStatus");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetStatus(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Status object from lua table
							CharacterStatus status;
							status.name = get_string_value_from_table("Name");
							status.effect = get_string_value_from_table("Effect");
							status.effect_length = (uint8_t)get_number_value_from_table("EffectLength");
							status.status_type = (CharacterStatusTypes)get_number_value_from_table("StatusType");

							// push Status object to game environment vector
							s.push_back(status);

							// pop table off lua stack
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
			// get number of Weapons from global lua variable
			int num_weapons = (int)get_global_number_variable("num_weapons");

			// use lua GetWeapon function to retrieve each individual Weapon object
			for (int i = 0; i < num_weapons; i++) {
				lua_getglobal(L, "GetWeapon");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetWeapon(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Weapon object from lua table
							CharacterWeapon weapon;
							weapon.collection_index = (uint8_t)get_number_value_from_table("CollectionIndex");
							weapon.category = (WeaponCategory)get_number_value_from_table("Category");
							weapon.handling = (WeaponHandling)get_number_value_from_table("Handling");
							weapon.weight = (WeaponWeight)get_number_value_from_table("Weight");
							weapon.range = (WeaponRange)get_number_value_from_table("Range");
							weapon.damage_type = (WeaponDamageType)get_number_value_from_table("DamageType");
							weapon.name = get_string_value_from_table("Name");
							weapon.element = (CharacterElements)get_number_value_from_table("Element");
							weapon.strength = (uint8_t)get_number_value_from_table("Strength");
							weapon.can_inflict_status = get_bool_value_from_table("CanInflictStatus");

							if (weapon.can_inflict_status) {
								weapon.inflicted_status = (uint8_t)get_number_value_from_table("InflictedStatus");
							}
							else {
								weapon.inflicted_status = 0;
							}

							// push Weapon object to game environment vector
							w.push_back(weapon);

							// pop table off lua stack
							lua_pop(L, 1);
						}
					}
				}
			}

			return true;
		}

		// Parses each Passive Ability object found in settings file
		bool LuaHandler::parse_passive_abilities(std::vector<CharacterPassiveAbility>& p_abil)
		{
			// use lua GetPassiveAbility function to retrieve each individual Passive Ability object
			for (int i = 0; i <= (int)CharacterElements::ALPHA; i++) {
				lua_getglobal(L, "GetPassiveAbility");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetPassiveAbility(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Passive Ability object from lua table
							CharacterPassiveAbility passive_ability;
							passive_ability.name = get_string_value_from_table("Name");
							passive_ability.effect = get_string_value_from_table("Effect");
							passive_ability.native_element = (CharacterElements)get_number_value_from_table("NativeElement");

							// push Passive Ability object to game environment vector
							p_abil.push_back(passive_ability);

							// pop table off lua stack
							lua_pop(L, 1);
						}
					}
				}
			}

			return true;
		}

		// Parses each Special Ability object found in settings file
		bool LuaHandler::parse_special_abilities(std::vector<CharacterSpecialAbility>& s_abil)
		{
			// get number of Special Abilities from global lua variable
			int num_special_abilities = (int)get_global_number_variable("num_special_abilities");

			// use lua GetSpecialAbility function to retrieve each individual Special Ability object
			for (int i = 0; i < num_special_abilities; i++) {
				lua_getglobal(L, "GetSpecialAbility");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetSpecialAbility(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Special Ability object from lua table
							CharacterSpecialAbility special_ability;
							special_ability.name = get_string_value_from_table("Name");
							special_ability.effect = get_string_value_from_table("Effect");
							special_ability.cost_to_learn = (uint16_t)get_number_value_from_table("CostToLearn");

							// construct Special Ability Requirements from WeaponReqs and ElementSupport properties
							CharacterSpecialAbilityRequirements reqs;
							std::bitset<2> weapon_reqs = (uint8_t)get_number_value_from_table("WeaponReqs");
							std::bitset<6> element_support = (uint8_t)get_number_value_from_table("ElementSupport");

							reqs.melee_range_weapon_needed = weapon_reqs[1];
							reqs.long_range_weapon_needed = weapon_reqs[0];

							reqs.basic_element_supported = element_support[5];
							reqs.earth_element_supported = element_support[4];
							reqs.air_element_supported = element_support[3];
							reqs.fire_element_supported = element_support[2];
							reqs.water_element_supported = element_support[1];
							reqs.mystic_element_supported = element_support[0];

							special_ability.requirements = reqs;

							// push Special Ability object to game environment vector
							s_abil.push_back(special_ability);

							// pop table off lua stack
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
		bool LuaHandler::parse_settings_file(std::string file_name, 
			std::vector<CharacterElement>& e, 
			std::vector<CharacterRank>& r, 
			std::vector<CharacterStatus>& s, 
			std::vector<CharacterWeapon>& w,
			std::vector<CharacterPassiveAbility>& p_abil,
			std::vector<CharacterSpecialAbility>& s_abil)
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
			parse_passive_abilities(p_abil);
			parse_special_abilities(s_abil);

			// close lua state machine
			lua_close(L);
			return true;
		}
	}
}
