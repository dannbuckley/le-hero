/**
 * LuaHandler.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <bitset>
#include <exception>
#include <iostream>
#include "LuaHandler.h"
#include "spdlog/spdlog.h"

namespace le_hero {
	namespace lua {
		struct unexpected_type_error : public std::exception {
			const char* what() const throw() {
				return "Unexpected type encountered when parsing Lua file. See 'log.txt' for more info.";
			}
		};

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

		std::string LuaHandler::get_global_string_variable(std::string var_name)
		{
			// get global variable var_name
			lua_getglobal(L, var_name.c_str());

			// check for valid type
			if (!lua_isstring(L, -1)) {
				// throw exception for unexpected type
				spdlog::get("logger")->error("Unexpected type for Lua global variable in call LuaHandler::get_global_string_variable({})", var_name);
				throw unexpected_type_error();
			}

			// convert value to string
			std::string var_value = lua_tostring(L, -1);

			// pop value off lua stack
			lua_pop(L, 1);
			return var_value;
		}

		// Retrieves number-type value of global variable var_name from lua file
		lua_Number LuaHandler::get_global_number_variable(std::string var_name)
		{
			// get global variable var_name
			lua_getglobal(L, var_name.c_str());

			// check for valid type
			if (!lua_isnumber(L, -1)) {
				// throw exception for unexpected type
				spdlog::get("logger")->error("Unexpected type for Lua global variable in call LuaHandler::get_global_number_variable({})", var_name);
				throw unexpected_type_error();
			}

			// convert value to number
			int var_value = lua_tonumber(L, -1);

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

			// check for valid type
			if (!lua_isstring(L, -1)) {
				// throw exception for unexpected type
				spdlog::get("logger")->error("Unexpected type for Lua table value in call LuaHandler::get_string_value_from_table({})", key);
				throw unexpected_type_error();
			}

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

			// check for valid type
			if (!lua_isnumber(L, -1)) {
				// throw exception for unexpected type
				spdlog::get("logger")->error("Unexpected type for Lua table value in call LuaHandler::get_number_value_from_table({})", key);
				throw unexpected_type_error();
			}

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

			// check for valid type
			if (!lua_isboolean(L, -1)) {
				// throw exception for unexpected type
				spdlog::get("logger")->error("Unexpected type for Lua table value in call LuaHandler::get_bool_value_from_table({})", key);
				throw unexpected_type_error();
			}

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

							try {
								element.name = get_string_value_from_table("Name");
								element.armor_percent = (uint8_t)get_number_value_from_table("ArmorPercent");
								element.armor_turns = (uint8_t)get_number_value_from_table("ArmorTurns");
								element.base_attack = (uint8_t)get_number_value_from_table("BaseAttack");
								element.base_speed = (uint8_t)get_number_value_from_table("BaseSpeed");
								element.base_health = (uint8_t)get_number_value_from_table("BaseHealth");
								element.element_identifier = (CharacterElements)i;
							}
							catch (unexpected_type_error& e) {
								std::cout << e.what() << std::endl;
								return false;
							}

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

							try {
								rank.name = get_string_value_from_table("Name");
								rank.attack_boost = (uint8_t)get_number_value_from_table("AttackBoost");
								rank.speed_boost = (uint8_t)get_number_value_from_table("SpeedBoost");
								rank.health_boost = (uint8_t)get_number_value_from_table("HealthBoost");
							}
							catch (unexpected_type_error& e) {
								std::cout << e.what() << std::endl;
								return false;
							}

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
			int num_statuses = 0;
			try {
				num_statuses = (int)get_global_number_variable("num_statuses");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

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

							try {
								status.name = get_string_value_from_table("Name");
								status.effect = get_string_value_from_table("Effect");
								status.effect_length = (uint8_t)get_number_value_from_table("EffectLength");
								status.status_type = (CharacterStatusTypes)get_number_value_from_table("StatusType");
							}
							catch (unexpected_type_error& e) {
								std::cout << e.what() << std::endl;
								return false;
							}

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
			int num_weapons = 0;
			try {
				num_weapons = (int)get_global_number_variable("num_weapons");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

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

							try {
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
							}
							catch (unexpected_type_error& e) {
								std::cout << e.what() << std::endl;
								return false;
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

							try {
								passive_ability.name = get_string_value_from_table("Name");
								passive_ability.effect = get_string_value_from_table("Effect");
								passive_ability.native_element = (CharacterElements)i;
							}
							catch (unexpected_type_error& e) {
								std::cout << e.what() << std::endl;
								return false;
							}

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
			int num_special_abilities = 0;
			try {
				num_special_abilities = (int)get_global_number_variable("num_special_abilities");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

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

							try {
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
							}
							catch (unexpected_type_error& e) {
								std::cout << e.what() << std::endl;
								return false;
							}

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

		// Parses each Item object found in settings file
		bool LuaHandler::parse_items(std::vector<CharacterItem>& im)
		{
			// get number of Items from global lua variable
			int num_items = 0;
			try {
				num_items = (int)get_global_number_variable("num_items");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// use lua GetSpecialAbility function to retrieve each individual Item object
			for (int i = 0; i < num_items; i++) {
				lua_getglobal(L, "GetItem");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetItem(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Item object from lua table
							CharacterItem item;

							try {
								item.name = get_string_value_from_table("Name");
								item.effect = get_string_value_from_table("Effect");
								item.item_type = (CharacterItemType)get_number_value_from_table("ItemType");
								item.item_rank = (CharacterItemRank)get_number_value_from_table("ItemRank");
								item.item_element = (CharacterElements)get_number_value_from_table("ItemElement");
								item.cost = (uint32_t)get_number_value_from_table("Cost");
								item.available_at_level = (uint8_t)get_number_value_from_table("AvailableAtLevel");
							}
							catch (unexpected_type_error& e) {
								std::cout << e.what() << std::endl;
								return false;
							}

							// push Special Ability object to game environment vector
							im.push_back(item);

							// pop table off lua stack
							lua_pop(L, 1);
						}
					}
				}
			}

			return true;
		}

		// Parses each Quest reference found in quests index file
		bool LuaHandler::parse_quest_references(std::vector<std::pair<std::string, std::string>>& qr)
		{
			// get number of Quest references from global lua variable
			int num_quests = 0;
			try {
				num_quests = (int)get_global_number_variable("num_quests");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// use lua GetQuestRef function to retrieve each individual Quest reference
			for (int i = 0; i < num_quests; i++) {
				lua_getglobal(L, "GetQuestRef");
				if (lua_isfunction(L, -1)) {
					// push reference index number onto lua stack
					lua_pushnumber(L, i);

					// call GetQuestRef(i)
					if (validate_lua(lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Quest reference from lua table
							std::pair<std::string, std::string> quest_ref;

							try {
								std::string quest_file = get_string_value_from_table("QuestFile");
								std::string quest_name = get_string_value_from_table("QuestName");

								quest_ref = std::make_pair(quest_file, quest_name);
							}
							catch (unexpected_type_error& e) {
								std::cout << e.what() << std::endl;
								return false;
							}

							// push Quest reference to game environment vector
							qr.push_back(quest_ref);

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

		// Destructor
		LuaHandler::~LuaHandler()
		{
			lua_close(L);
		}

		// Parses settings file for game environment
		bool LuaHandler::parse_settings_file(std::string file_name,
			std::string& quests_index_file,
			std::vector<CharacterElement>& e, 
			std::vector<CharacterRank>& r, 
			std::vector<CharacterStatus>& s, 
			std::vector<CharacterWeapon>& w,
			std::vector<CharacterPassiveAbility>& p_abil,
			std::vector<CharacterSpecialAbility>& s_abil,
			std::vector<CharacterItem>& im)
		{
			// ensure integrity of settings file
			if (!validate_lua(luaL_dofile(L, file_name.c_str()))) {
				return false;
			}

			try {
				quests_index_file = get_global_string_variable("quests_index_file");
			}
			catch (unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			// parse game data from settings file
			if (!parse_elements(e)) {
				return false;
			}

			if (!parse_ranks(r)) {
				return false;
			}

			if (!parse_statuses(s)) {
				return false;
			}

			if (!parse_weapons(w)) {
				return false;
			}

			if (!parse_passive_abilities(p_abil)) {
				return false;
			}

			if (!parse_special_abilities(s_abil)) {
				return false;
			}

			if (!parse_items(im)) {
				return false;
			}

			return true;
		}

		bool LuaHandler::parse_quest_file(std::string quest_file)
		{
			// ensure integrity of quest file
			if (!validate_lua(luaL_dofile(L, quest_file.c_str()))) {
				return false;
			}

			// parse quest data
			
			return true;
		}

		// Parses quests index file for game environment
		bool LuaHandler::parse_quests_index_file(std::string quests_index_file, std::vector<std::pair<std::string, std::string>>& qr)
		{
			// ensure integrity of index file
			if (!validate_lua(luaL_dofile(L, quests_index_file.c_str()))) {
				return false;
			}

			// parse references to quest files
			if (!parse_quest_references(qr)) {
				return false;
			}

			return true;
		}
	}
}
