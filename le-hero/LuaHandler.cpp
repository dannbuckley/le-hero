/**
 * LuaHandler.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <bitset>
#include <iostream>
#include "LuaDefaults.h"
#include "LuaHandler.h"
#include "Timer.h"

namespace le_hero {
	namespace lua {
		// Parses each Element object found in settings file
		bool LuaHandler::parse_elements(std::vector<CharacterElement>& e)
		{
			e.reserve((size_t)CharacterElements::ALPHA + 1);

			// use lua GetElement function to retrieve each individual Element object
			for (unsigned int i = 0; i <= (unsigned int)CharacterElements::ALPHA; i++) {
				lua_getglobal(L, "GetElement");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetElement(i)
					if (LuaHelpers::validate_lua(L, lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Element object from lua table
							CharacterElement element;

							try {
								element.name = LuaHelpers::get_string_value_from_table(L, "Name");
								element.armor_percent = (uint8_t)LuaHelpers::get_number_value_from_table(L, "ArmorPercent");
								element.armor_turns = (uint8_t)LuaHelpers::get_number_value_from_table(L, "ArmorTurns");
								element.base_attack = (uint8_t)LuaHelpers::get_number_value_from_table(L, "BaseAttack");
								element.base_speed = (uint8_t)LuaHelpers::get_number_value_from_table(L, "BaseSpeed");
								element.base_health = (uint8_t)LuaHelpers::get_number_value_from_table(L, "BaseHealth");
								element.element_identifier = (CharacterElements)i;
							}
							catch (exception::unexpected_type_error& e) {
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
			r.reserve((size_t)CharacterRanks::Z + 1);

			// use lua GetRank function to retrieve each individual Rank object
			for (unsigned int i = 0; i <= (unsigned int)CharacterRanks::Z; i++) {
				lua_getglobal(L, "GetRank");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetRank(i)
					if (LuaHelpers::validate_lua(L, lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Rank object from lua table
							CharacterRank rank;

							try {
								rank.name = LuaHelpers::get_string_value_from_table(L, "Name");
								rank.attack_boost = (uint8_t)LuaHelpers::get_number_value_from_table(L, "AttackBoost");
								rank.speed_boost = (uint8_t)LuaHelpers::get_number_value_from_table(L, "SpeedBoost");
								rank.health_boost = (uint8_t)LuaHelpers::get_number_value_from_table(L, "HealthBoost");
							}
							catch (exception::unexpected_type_error& e) {
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
			size_t num_statuses = 0;
			try {
				num_statuses = (size_t)LuaHelpers::get_global_number_variable(L, "num_statuses");
			}
			catch (exception::unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			s.reserve(num_statuses);

			// use lua GetStatus function to retrieve each individual Status object
			for (unsigned int i = 0; i < num_statuses; i++) {
				lua_getglobal(L, "GetStatus");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetStatus(i)
					if (LuaHelpers::validate_lua(L, lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Status object from lua table
							CharacterStatus status;
							status.index = i;

							try {
								status.name = LuaHelpers::get_string_value_from_table(L, "Name");
								status.effect = LuaHelpers::get_string_value_from_table(L, "Effect");
								status.effect_length = (uint8_t)LuaHelpers::get_number_value_from_table(L, "EffectLength");
								status.status_type = (CharacterStatusTypes)LuaHelpers::get_number_value_from_table(L, "StatusType");
							}
							catch (exception::unexpected_type_error& e) {
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
			size_t num_weapons = 0;
			try {
				num_weapons = (size_t)LuaHelpers::get_global_number_variable(L, "num_weapons");
			}
			catch (exception::unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			w.reserve(num_weapons);

			// use lua GetWeapon function to retrieve each individual Weapon object
			for (unsigned int i = 0; i < num_weapons; i++) {
				lua_getglobal(L, "GetWeapon");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetWeapon(i)
					if (LuaHelpers::validate_lua(L, lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Weapon object from lua table
							CharacterWeapon weapon;

							try {
								weapon.collection_index = (uint8_t)LuaHelpers::get_number_value_from_table(L, "CollectionIndex");
								weapon.category = (WeaponCategory)LuaHelpers::get_number_value_from_table(L, "Category");
								weapon.handling = (WeaponHandling)LuaHelpers::get_number_value_from_table(L, "Handling");
								weapon.weight = (WeaponWeight)LuaHelpers::get_number_value_from_table(L, "Weight");
								weapon.range = (WeaponRange)LuaHelpers::get_number_value_from_table(L, "Range");
								weapon.damage_type = (WeaponDamageType)LuaHelpers::get_number_value_from_table(L, "DamageType");
								weapon.name = LuaHelpers::get_string_value_from_table(L, "Name");
								weapon.element = (CharacterElements)LuaHelpers::get_number_value_from_table(L, "Element");
								weapon.strength = (uint8_t)LuaHelpers::get_number_value_from_table(L, "Strength");
								weapon.can_inflict_status = LuaHelpers::get_bool_value_from_table(L, "CanInflictStatus");

								if (weapon.can_inflict_status) {
									weapon.inflicted_status = (uint8_t)LuaHelpers::get_number_value_from_table(L, "InflictedStatus");
								}
								else {
									weapon.inflicted_status = 0;
								}
							}
							catch (exception::unexpected_type_error& e) {
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
			p_abil.reserve((size_t)CharacterElements::ALPHA + 1);

			// use lua GetPassiveAbility function to retrieve each individual Passive Ability object
			for (unsigned int i = 0; i <= (unsigned int)CharacterElements::ALPHA; i++) {
				lua_getglobal(L, "GetPassiveAbility");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetPassiveAbility(i)
					if (LuaHelpers::validate_lua(L, lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Passive Ability object from lua table
							CharacterPassiveAbility passive_ability;

							try {
								passive_ability.name = LuaHelpers::get_string_value_from_table(L, "Name");
								passive_ability.effect = LuaHelpers::get_string_value_from_table(L, "Effect");
								passive_ability.native_element = (CharacterElements)i;
							}
							catch (exception::unexpected_type_error& e) {
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
			size_t num_special_abilities = 0;
			try {
				num_special_abilities = (size_t)LuaHelpers::get_global_number_variable(L, "num_special_abilities");
			}
			catch (exception::unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			s_abil.reserve(num_special_abilities);

			// use lua GetSpecialAbility function to retrieve each individual Special Ability object
			for (unsigned int i = 0; i < num_special_abilities; i++) {
				lua_getglobal(L, "GetSpecialAbility");
				if (lua_isfunction(L, -1)) {
					// push object index number onto lua stack
					lua_pushnumber(L, i);

					// call GetSpecialAbility(i)
					if (LuaHelpers::validate_lua(L, lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Special Ability object from lua table
							CharacterSpecialAbility special_ability;

							try {
								special_ability.name = LuaHelpers::get_string_value_from_table(L, "Name");
								special_ability.effect = LuaHelpers::get_string_value_from_table(L, "Effect");
								special_ability.cost_to_learn = (uint16_t)LuaHelpers::get_number_value_from_table(L, "CostToLearn");

								// construct Special Ability Requirements from WeaponReqs and ElementSupport properties
								CharacterSpecialAbilityRequirements reqs;
								std::bitset<2> weapon_reqs = (uint8_t)LuaHelpers::get_number_value_from_table(L, "WeaponReqs");
								std::bitset<6> element_support = (uint8_t)LuaHelpers::get_number_value_from_table(L, "ElementSupport");

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
							catch (exception::unexpected_type_error& e) {
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

		// Parses each Quest reference found in quests index file
		bool LuaHandler::parse_quest_references(std::vector<std::pair<std::string, std::string>>& qr)
		{
			// get number of Quest references from global lua variable
			size_t num_quests = 0;
			try {
				num_quests = (size_t)LuaHelpers::get_global_number_variable(L, "num_quests");
			}
			catch (exception::unexpected_type_error& e) {
				std::cout << e.what() << std::endl;
				return false;
			}

			qr.reserve(num_quests);

			// use lua GetQuestRef function to retrieve each individual Quest reference
			for (unsigned int i = 0; i < num_quests; i++) {
				lua_getglobal(L, "GetQuestRef");
				if (lua_isfunction(L, -1)) {
					// push reference index number onto lua stack
					lua_pushnumber(L, i);

					// call GetQuestRef(i)
					if (LuaHelpers::validate_lua(L, lua_pcall(L, 1, 1, 0))) {
						if (lua_istable(L, -1)) {
							// construct Quest reference from lua table
							std::pair<std::string, std::string> quest_ref;

							try {
								std::string quest_file = LuaHelpers::get_string_value_from_table(L, "QuestFile");
								std::string quest_name = LuaHelpers::get_string_value_from_table(L, "QuestName");

								quest_ref = std::make_pair(quest_file, quest_name);
							}
							catch (exception::unexpected_type_error& e) {
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
		LuaHandler::LuaHandler(): L(nullptr)
		{
		}

		// Parses settings file for game environment
		bool LuaHandler::parse_settings_file(const char* file_name,
			std::string& quests_index_file,
			std::vector<CharacterElement>& e, 
			std::vector<CharacterRank>& r, 
			std::vector<CharacterStatus>& s, 
			std::vector<CharacterWeapon>& w,
			std::vector<CharacterPassiveAbility>& p_abil,
			std::vector<CharacterSpecialAbility>& s_abil)
		{
			PROFILE_TIMER(); // record the time elapsed for debugging

			L = luaL_newstate(); // initialize lua stack
			luaL_openlibs(L); // enable lua standard libraries

			// ensure integrity of settings file
			if (!LuaHelpers::validate_lua(L, luaL_dofile(L, file_name))) {
				return false;
			}

			try {
				quests_index_file = LuaHelpers::get_global_string_variable(L, "quests_index_file");
			}
			catch (exception::unexpected_type_error& e) {
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

			// close lua state
			lua_close(L);
			return true;
		}

		// Parses quests index file for game environment
		bool LuaHandler::parse_quests_index_file(std::string quests_index_file, std::vector<std::pair<std::string, std::string>>& qr)
		{
			PROFILE_TIMER(); // record the time elapsed for debugging

			L = luaL_newstate(); // initialize lua stack
			luaL_openlibs(L); // enable lua standard libraries

			// ensure integrity of index file
			if (!LuaHelpers::validate_lua(L, luaL_dofile(L, quests_index_file.c_str()))) {
				return false;
			}

			// parse references to quest files
			if (!parse_quest_references(qr)) {
				return false;
			}

			// close lua state
			lua_close(L);
			return true;
		}
	}
}