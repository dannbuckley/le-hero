/**
 * Game.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <stack>
#include "LuaHandler.h"
#include "StateHandler.h"

namespace le_hero {
	class Game : public state::StateHandler
	{
	private:
		std::unique_ptr<lua::LuaHandler> lua_handler;
		std::unique_ptr<std::stack<enum state::StateTypes>> state_handler;

		/* Game Data */

		std::vector<CharacterElement> elements;
		std::vector<CharacterRank> ranks;
		std::vector<CharacterStatus> statuses;
		std::vector<CharacterWeapon> weapons;
		std::vector<CharacterPassiveAbility> passive_abilities;
		std::vector<CharacterSpecialAbility> special_abilities;
		std::vector<CharacterItem> items;

		/* Quest Data */

		std::vector<std::pair<std::string, std::string>> quest_references;

		/* Debug Variables */

		std::vector<enum state::StateTypes> state_history;
		std::vector<enum state::StateActions> action_history;

		/* State Action Handlers */

		bool act_in_stateless(enum state::StateActions action);
		bool act_in_initializing(enum state::StateActions action);
		bool act_in_parsing(enum state::StateActions action);

	protected:
		bool exit_current_state();

	public:
		Game(std::string settings_file);

		CharacterElement get_element(uint8_t index);
		CharacterRank get_rank(uint8_t index);
		CharacterStatus get_status(uint8_t index);
		CharacterWeapon get_weapon(uint8_t index);
		CharacterPassiveAbility get_passive_ability(uint8_t index);
		CharacterSpecialAbility get_special_ability(uint8_t index);
		CharacterItem get_item(uint8_t index);

		size_t get_num_statuses();
		size_t get_num_weapons();
		size_t get_num_special_abilities();
		size_t get_num_items();

		bool act(enum state::StateActions action);
		enum state::StateTypes get_current_state();
	};
}

