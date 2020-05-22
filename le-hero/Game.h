/**
 * Game.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "LuaHandler.h"

namespace le_hero {
	class Game
	{
	private:
		std::unique_ptr<lua::LuaHandler> lua_handler;

		std::vector<CharacterElement> elements;
		std::vector<CharacterRank> ranks;
		std::vector<CharacterStatus> statuses;
		std::vector<CharacterWeapon> weapons;
		std::vector<CharacterPassiveAbility> passive_abilities;
		std::vector<CharacterSpecialAbility> special_abilities;

	public:
		Game(std::string settings_file);

		CharacterElement get_element(uint8_t index);
		CharacterRank get_rank(uint8_t index);
		CharacterStatus get_status(uint8_t index);
		CharacterWeapon get_weapon(uint8_t index);
		CharacterPassiveAbility get_passive_ability(uint8_t index);
		CharacterSpecialAbility get_special_ability(uint8_t index);

		size_t get_num_statuses();
		size_t get_num_weapons();
		size_t get_num_special_abilities();
	};
}

