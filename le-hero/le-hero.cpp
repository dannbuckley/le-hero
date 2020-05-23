/**
 * le-hero.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <iostream>
#include <fstream>
#include "CharacterBattleHandler.h"

// gabime/spdlog, installed via vcpkg
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

int main()
{
    // make sure the log file exists
    std::ofstream log_file("log.txt");
    log_file << "Booting le-hero." << std::endl;
    log_file.close();

    // use log file for spdlog
    try {
        auto logger = spdlog::basic_logger_mt("logger", "log.txt");
    }
    catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Logger initialization failed: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    // print success message
    spdlog::get("logger")->info("Logger initialized successfully.");

    spdlog::set_level(spdlog::level::debug);

    std::shared_ptr<le_hero::Game> game;

    try {
        game = std::make_shared<le_hero::Game>("base.lua");
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::shared_ptr<le_hero::Character> character = std::make_shared<le_hero::Character>(game);
    std::shared_ptr<le_hero::CharacterBattleHandler> character_battle = std::make_shared<le_hero::CharacterBattleHandler>(character);

    return EXIT_SUCCESS;
}
