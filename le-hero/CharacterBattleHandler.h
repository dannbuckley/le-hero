/**
 * CharacterBattleHandler.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include "Character.h"

namespace le_hero {
    enum class CharacterActionTypes : uint8_t {
        PASS = 0,
        WEAPON,
        SPECIAL_ABILITY,
    };

    class CharacterBattleHandler
    {
    private:
        std::shared_ptr<Character> base;

        bool ready = false;
        bool currently_in_battle = false;
        enum CharacterElements area_terrain = CharacterElements::BASIC;
        enum CharacterActionTypes selected_action = CharacterActionTypes::PASS;
        float attack_modifier = 1.0f;
        float speed_modifier = 1.0f;
        uint16_t current_health = 0;

        bool locked_on_pass = false;
        bool locked_on_weapon = false;
        bool locked_on_special = false;

        bool pass_disabled = false;
        bool weapon_disabled = false;
        bool special_disabled = false;

        CharacterStatus inflicted_status;
        uint8_t status_turns_left = 0;
        uint8_t armor_turns_left = 0;
        bool protected_from_damage = false;

        uint16_t damage_dealt = 0;

    public:
        CharacterBattleHandler();
        CharacterBattleHandler(std::shared_ptr<Character> base);

        bool is_ready();
        bool is_in_battle();

        bool cure_status();
        bool inflict_status(CharacterStatus new_status);
        bool restore_armor();

        uint16_t calculate_battle_attack_stat();
        uint16_t calculate_battle_speed_stat();

        uint16_t get_current_health();
        uint16_t damage_health(uint16_t amount, bool bypass_armor = false);
        uint16_t restore_health(uint16_t amount);

        void end_battle();
        void new_turn();
        void perform_action(std::shared_ptr<CharacterBattleHandler> enemy);
        void register_battle(enum CharacterElements terrain);
        void reset_stats(bool reset_all = false);
        void reset_turn_data();
        void select_action(enum CharacterActionTypes action);

        bool use_item(uint8_t item_index);

        void obtain_quest_prizes(uint32_t prize_coins,
            uint16_t prize_experience,
            std::vector<uint8_t> prize_items,
            std::vector<uint8_t> prize_weapons);
    };
}

