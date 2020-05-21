/**
 * le-hero.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <iostream>
#include "Game.h"

int main()
{
    std::unique_ptr<le_hero::Game> game = std::make_unique<le_hero::Game>("base.lua");
    return EXIT_SUCCESS;
}
