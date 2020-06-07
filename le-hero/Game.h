/**
 * Game.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "LuaHandler.h"
#include "StateHandler.h"

namespace le_hero {
	using namespace state;
	namespace game {
		extern void initialize_game_environment(const char* settings_file);
		extern bool game_act(enum StateActions action);
		extern enum StateTypes get_current_state();

		extern const CharacterElement& get_element(uint8_t index);
		extern const CharacterRank& get_rank(uint8_t index);
		extern const CharacterStatus& get_status(uint8_t index);
		extern const CharacterWeapon& get_weapon(uint8_t index);
		extern const CharacterPassiveAbility& get_passive_ability(uint8_t index);
		extern const CharacterSpecialAbility& get_special_ability(uint8_t index);
		extern const CharacterItem& get_item(uint8_t index);
		extern const std::pair<std::string, std::string>& get_quest_ref(uint8_t index);

		extern const size_t get_num_statuses();
		extern const size_t get_num_weapons();
		extern const size_t get_num_special_abilities();
		extern const size_t get_num_items();
		extern const size_t get_num_quest_refs();
	}
}