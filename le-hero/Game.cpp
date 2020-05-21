/**
 * Game.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "Game.h"

namespace le_hero {
    Game::Game(std::string settings_file)
    {
        lua_handler = std::make_unique<lua::LuaHandler>();
        lua_handler->parse_file(settings_file, elements, ranks, statuses, weapons);
    }
}
