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
    class Character
    {
    private:
        const uint32_t COINS_MAX = 1000000000U;
        const uint16_t EXPERIENCE_MAX = 31500U;
        const uint8_t LEVEL_MAX = 250U;
        const uint8_t ITEM_AMOUNT_MAX = 100U;

        std::shared_ptr<Game> env;

        CharacterSpecialAbility acquired_ability;
        uint32_t coins = 0;
        CharacterElement element;
        uint16_t total_experience = 0;
        uint16_t available_experience = 0;
        uint8_t level = 0;
        CharacterPassiveAbility passive_ability;
        CharacterRank rank;
        CharacterWeapon weapon;

        std::vector<uint8_t> vault;
        std::vector<uint8_t> inventory;
        std::vector<bool> library;

        double _calculate_correction_value(uint8_t _level);
        uint16_t _calculate_attack_stat();
        uint16_t _calculate_speed_stat();
        uint16_t _calculate_health_stat();
        uint16_t _calculate_exp_at_level(uint8_t _level);
        uint16_t _calculate_exp_to_next_level();

        void update_level();

    public:
        Character(std::shared_ptr<Game> game_env);

        void gain_coins(uint32_t coin_yield);
        void gain_exp(uint16_t exp_yield);

        bool change_special_ability(uint8_t new_spec_abil);
        bool learn_special_ability(uint8_t new_spec_abil);
        bool spend_coins(uint32_t coin_amount);
        bool verify_special_ability_requirements(CharacterSpecialAbilityRequirements reqs);

        bool has_item(uint8_t item_index);
        bool item_availability_level_check(uint8_t item_level);

        bool acquire_item(uint8_t item_index);
        bool buy_item(uint8_t item_index);
        bool remove_item(uint8_t item_index, uint8_t amount);
    };
}
