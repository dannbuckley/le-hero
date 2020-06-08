/**
 * le-hero.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <iostream>
#include <fstream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "LuaQuestHandler.h"
#include "CharacterBattleHandler.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

// gabime/spdlog, installed via vcpkg
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

int main(int argc, char* argv[])
{
    // make sure the log file exists
    std::ofstream log_file("log.txt");
    log_file << "Booting le-hero." << std::endl;
    log_file.close();

    // use log file for spdlog
    try {
        auto logger = spdlog::basic_logger_mt("logger", "log.txt");
        auto graphics_logger = spdlog::stdout_color_mt("graphics_logger");
    }
    catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Logger initialization failed: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    // print success message
    spdlog::get("logger")->info("Logger initialized successfully.");

    // show debug messages in log file
    spdlog::set_level(spdlog::level::debug);

    // create the game environment using the base settings file
    try {
        le_hero::game::initialize_game_environment("base.lua");
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // create the player's character using the game environment
    std::shared_ptr<le_hero::Character> character = std::make_shared<le_hero::Character>();
    std::shared_ptr<le_hero::CharacterBattleHandler> character_battle = std::make_shared<le_hero::CharacterBattleHandler>(character);

    // create object to parse quest files
    std::shared_ptr<le_hero::lua::LuaQuestHandler> lua_quest_handler = std::make_shared<le_hero::lua::LuaQuestHandler>();

    // parse and load all quest data
    le_hero::game::game_act(le_hero::state::StateActions::START_PARSING_QUEST_FILES);
    std::vector<le_hero::quest::Quest> quests;
    try {
        quests = lua_quest_handler->load_all_quests();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    le_hero::game::game_act(le_hero::state::StateActions::FINISH_PARSING_QUEST_FILES);

    spdlog::get("logger")->info("Quest data parsed successfully.");
    
    using namespace le_hero::graphics;

    // create SDL renderer object with default window size
    Renderer r;

    // check if renderer has been initialized
    if (!r.is_initialized()) {
        // SDL initialization process failed at some point
        return EXIT_FAILURE;
    }

    {
        // vertex array
        float positions[] = {
            -2.0f, -1.5f, 0.0f, 1.0f, // 0
             2.0f, -1.5f, 1.0f, 1.0f, // 1
             2.0f,  1.5f, 1.0f, 0.0f, // 2
            -2.0f,  1.5f, 0.0f, 0.0f, // 3
        };

        // index array
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        va.add_buffer(vb, layout);

        IndexBuffer ib(indices, 6);

        // orthographic projection matrix
        glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

        // load shader and apply projection matrix
        Shader shader("game.shader");
        shader.bind();
        shader.set_uniform_mat_4f("u_MVP", projection);

        // load temporary loading screen texture
        Texture texture("img/RGBLoadingScreen.png");
        texture.bind();
        shader.set_uniform_1i("u_Texture", 0);

        // unbind all objects
        va.unbind();
        shader.unbind();
        vb.unbind();
        ib.unbind();

        // main display loop
        bool active = true;
        SDL_Event e;

        while (active) {
            // handle SDL events
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    active = false;
                }
            }

            // update display
            r.clear();
            shader.bind();
            r.draw(va, ib, shader);

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            // swap OpenGL buffer for window
            r.swap_buffers();
        }
    }

    // free SDL resources
    r.quit();

    return EXIT_SUCCESS;
}