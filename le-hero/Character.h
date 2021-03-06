/**
 * Character.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <vector>
#include "CharacterElement.h"
#include "CharacterPassiveAbility.h"
#include "CharacterRank.h"
#include "CharacterSpecialAbility.h"
#include "CharacterWeapon.h"
#include "Game.h"

namespace le_hero {
    // Structure for holding Character metadata
    // Used for construction of Character class from savefile or quest enemy info
    struct CharacterMeta {
        enum CharacterElements element;
        enum CharacterRanks rank;
        uint16_t total_experience;
        uint16_t available_experience;
        uint8_t weapon_index;
        uint8_t special_ability_index;
        uint32_t coins;
        std::vector<bool> vault;
        std::vector<bool> library;
    };

    class Character
    {
    private:
        const uint32_t COINS_MAX = 1000000000U;
        const uint16_t EXPERIENCE_MAX = 31500U;
        const uint8_t LEVEL_MAX = 250U;

        CharacterSpecialAbility acquired_ability;
        uint32_t coins = 0;
        CharacterElement element;
        uint16_t total_experience = 0;
        uint16_t available_experience = 0;
        uint8_t level = 0;
        CharacterPassiveAbility passive_ability;
        CharacterRank rank;
        CharacterWeapon weapon;

        std::vector<bool> vault;
        std::vector<bool> library;

        double _calculate_correction_value(uint8_t _level);        

        void update_level();

    public:
        Character();
        Character(CharacterMeta meta);

        static uint16_t calculate_exp_at_level(uint8_t _level);
        uint16_t calculate_exp_to_next_level();

        uint16_t calculate_attack_stat();
        uint16_t calculate_speed_stat();
        uint16_t calculate_health_stat();

        uint8_t get_level();
        uint16_t get_experience();
        const CharacterElement& get_element() const;
        const CharacterRank& get_rank() const;
        const CharacterPassiveAbility& get_passive_ability() const;
        const CharacterWeapon& get_equipped_weapon() const;
        const CharacterSpecialAbility& get_special_ability() const;

        void gain_coins(uint32_t coin_yield);
        void gain_exp(uint16_t exp_yield);

        /* Special Ability Library */

        bool change_special_ability(uint8_t new_spec_abil);
        bool learn_special_ability(uint8_t new_spec_abil);
        bool spend_coins(uint32_t coin_amount);
        bool verify_special_ability_requirements(CharacterSpecialAbilityRequirements reqs);

        /* Weapons Vault */

        bool has_weapon(CharacterWeapon _weapon);
        bool has_weapon(uint8_t weapon_index);
        bool acquire_weapon(CharacterWeapon _weapon);
        bool acquire_weapon(uint8_t weapon_index);
        bool change_weapon(uint8_t weapon_index);
    };
}