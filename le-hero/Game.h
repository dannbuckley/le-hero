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
	public:
		Game(std::string settings_file);
	};
}

