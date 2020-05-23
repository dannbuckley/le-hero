/**
 * le-hero.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <iostream>
#include "CharacterBattleHandler.h"

int main()
{
    std::shared_ptr<le_hero::Game> game = std::make_shared<le_hero::Game>("base.lua");
    std::shared_ptr<le_hero::Character> character = std::make_shared<le_hero::Character>(game);
    std::shared_ptr<le_hero::CharacterBattleHandler> character_battle = std::make_shared<le_hero::CharacterBattleHandler>(character);

    return EXIT_SUCCESS;
}
