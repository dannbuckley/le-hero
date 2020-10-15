/**
 * le-hero.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <iostream>
#include <fstream>

// SDL2 and OpenGL
#include "GraphicsIncludes.h"

// OpenGL mathematics
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

//#include "Renderer.h"
//#include "VertexBuffer.h"
//#include "VertexBufferLayout.h"
//#include "IndexBuffer.h"
//#include "VertexArray.h"
//#include "Shader.h"
//#include "Texture.h"

// Dear ImGui
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

// gabime/spdlog, installed via vcpkg
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "LuaQuestHandler.h"
#include "CharacterBattleHandler.h"

void graphics_debug_callback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam) {
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        spdlog::get("graphics_logger")->critical("[OpenGL High Severity] {}", message);
        return;
    case GL_DEBUG_SEVERITY_MEDIUM:
        spdlog::get("graphics_logger")->error("[OpenGL Medium Severity] {}", message);
        return;
    case GL_DEBUG_SEVERITY_LOW:
        spdlog::get("graphics_logger")->warn("[OpenGL Low Severity] {}", message);
        return;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        spdlog::get("graphics_logger")->trace("[OpenGL Notification] {}", message);
        return;
    }

    // unknown level
    ASSERT(false);
}

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

    // create SDL window
    SDL_Init(SDL_INIT_VIDEO < 0);
    auto window = SDL_CreateWindow("",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1280,
        780,
        SDL_WINDOW_OPENGL);

    // initialize SDL image library
    IMG_Init(IMG_INIT_PNG);

    // set OpenGL version for SDL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // create OpenGL context for SDL
    auto gl_ctx = SDL_GL_CreateContext(window);
    auto glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        spdlog::get("graphics_logger")->error("[GLEW Error] {}", glewGetErrorString(glew_status));
        return EXIT_FAILURE;
    }
    SDL_GL_SetSwapInterval(1); // VSync

    // enable OpenGL debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)graphics_debug_callback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

    // initialize OpenGL viewport
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0.0f, 0.0f, 1280, 720);

    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // initialize SDL and OpenGL implementations for ImGui
    ImGui::StyleColorsLight();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_ctx);
    ImGui_ImplOpenGL3_Init();

    // demo ImGui state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // main loop
    bool active = true;
    SDL_Event e;
    while (active) {
        while (SDL_PollEvent(&e) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT) {
                active = false;
            }
        }

        // set background color to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // advance to next ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");

            ImGui::Text("This is some useful text.");
            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            if (ImGui::Button("Button")) {
                counter++;
            }
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (show_another_window) {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me")) {
                show_another_window = false;
            }
            ImGui::End();
        }

        // render ImGui content
        ImGui::Render();

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // swap SDL and OpenGL buffers
        SDL_GL_SwapWindow(window);
    }

    // destroy ImGui resources
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // destroy SDL resources
    SDL_GL_DeleteContext(gl_ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}