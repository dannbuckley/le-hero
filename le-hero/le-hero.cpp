/**
 * le-hero.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <iostream>
#include "Character.h"
#include "Game.h"

int main()
{
    std::shared_ptr<le_hero::Game> game = std::make_shared<le_hero::Game>("base.lua");
    std::shared_ptr<le_hero::Character> character = std::make_shared<le_hero::Character>(game);

    return EXIT_SUCCESS;
}
