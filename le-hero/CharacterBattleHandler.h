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

        uint8_t get_base_level();
        uint16_t get_base_exp_to_next_level();
        uint16_t get_base_exp();
        const CharacterPassiveAbility& get_passive_ability() const;
        const CharacterWeapon& get_equipped_weapon() const;
        const CharacterSpecialAbility& get_special_ability() const;

        void base_gain_exp(uint16_t yield);
        void base_gain_coins(uint32_t yield);

        bool is_ready();
        bool is_in_battle();

        enum CharacterActionTypes get_selected_action();

        bool cure_status();
        bool inflict_status(CharacterStatus new_status);
        bool inflict_status(uint8_t new_status);
        CharacterStatus get_inflicted_status();
        uint8_t get_status_turns_left();

        bool restore_armor();
        void remove_armor();
        uint8_t get_armor_turns_left();

        void protect_from_damage();

        uint16_t get_base_attack_stat();
        uint16_t get_base_speed_stat();

        uint16_t calculate_battle_attack_stat();
        uint16_t calculate_battle_speed_stat();

        uint16_t get_current_health();
        uint16_t get_maximum_health();
        uint16_t damage_health(uint16_t amount, bool bypass_armor = false);
        uint16_t restore_health(uint16_t amount);

        enum CharacterElements get_area_terrain();

        void apply_attack_modifier(float mod);
        void apply_speed_modifier(float mod);

        void lock_on_pass();
        void lock_on_weapon();
        void lock_on_special();

        void disable_pass();
        void disable_weapon();
        void disable_special();

        void register_damage_dealt(uint16_t damage);
        uint16_t get_damage_dealt();

        void end_battle();
        void new_turn();
        void register_battle(enum CharacterElements terrain);
        void reset_stats(bool reset_all = false);
        void reset_turn_data();
        void select_action(enum CharacterActionTypes action);
    };
}