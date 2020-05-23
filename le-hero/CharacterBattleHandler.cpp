/**
 * CharacterBattleHandler.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <bitset>
#include <cmath>
#include "CharacterBattleHandler.h"

namespace le_hero {
	CharacterBattleHandler::CharacterBattleHandler()
	{
        this->reset_turn_data();
        this->reset_stats(true);
	}

	CharacterBattleHandler::CharacterBattleHandler(std::shared_ptr<Character> base) : base(base)
    {
        this->reset_turn_data();
        this->reset_stats(true);
    }

	bool CharacterBattleHandler::is_ready()
	{
		return this->ready;
	}

    bool CharacterBattleHandler::is_in_battle()
    {
        return this->currently_in_battle;
    }

    bool CharacterBattleHandler::cure_status()
    {
        // check if the Character is currently inflicted with a status
        if (this->status_turns_left == 0) {
            return false;
        }

        // remove the Character's inflicted status
        this->inflicted_status = CharacterStatus();
        this->status_turns_left = 0;
        return true;
    }

    bool CharacterBattleHandler::inflict_status(CharacterStatus new_status)
    {
        // check if the Character is already inflicted with a status
        if (this->status_turns_left != 0) {
            return false;
        }

        // inflict the Character with the provided status
        this->inflicted_status = new_status;
        this->status_turns_left = new_status.effect_length;
        return true;
    }

    bool CharacterBattleHandler::restore_armor()
    {
        // check if the Character still has armor
        if (this->armor_turns_left != 0) {
            return false;
        }

        // completely restore the Character's armor
        this->armor_turns_left = this->base->get_element().armor_turns;
        return true;
    }

    uint16_t le_hero::CharacterBattleHandler::calculate_battle_attack_stat()
    {
        return (uint16_t)floorf(this->attack_modifier * this->base->calculate_attack_stat());
    }

    uint16_t CharacterBattleHandler::calculate_battle_speed_stat()
    {
        return (uint16_t)floorf(this->speed_modifier * this->base->calculate_speed_stat());
    }

    uint16_t CharacterBattleHandler::get_current_health()
    {
        return this->current_health;
    }

    uint16_t CharacterBattleHandler::damage_health(uint16_t amount, bool bypass_armor)
    {
        if (this->current_health == 0) {
            // the Character cannot receive any damage if health is completely depleted
            return 0;
        }
        else if (this->protected_from_damage) {
            // the Character cannot receive any damage if they are protected from damage;
            return this->current_health;
        }

        // calculate actual amount of damage
        uint16_t damage = 0;
        if (bypass_armor || (this->armor_turns_left == 0)) {
            damage = amount;
        }
        else {
            damage = (uint16_t)ceilf(amount * ((100.0f - this->base->get_element().armor_percent) / 100.0f));
        }

        // apply damage to Character's health
        if (damage >= this->current_health) {
            this->current_health = 0;
        }
        else {
            this->current_health -= damage;
        }

        // return amount of health left after taking damage
        return this->current_health;
    }

    uint16_t CharacterBattleHandler::restore_health(uint16_t amount)
    {
        uint16_t max_health = this->base->calculate_health_stat();
        if (this->current_health == max_health) {
            // the Character cannot receive any health if their health is full
            return this->current_health;
        }

        // calculate actual amount of health received
        uint16_t diff = max_health - this->current_health;
        if (amount >= diff) {
            this->current_health = max_health;
        }
        else {
            this->current_health += amount;
        }

        // return amount of health after healing
        return this->current_health;
    }

    void CharacterBattleHandler::end_battle()
    {
        reset_stats(true);
        reset_turn_data();
        this->area_terrain = CharacterElements::BASIC;
        this->currently_in_battle = false;
    }

    void CharacterBattleHandler::new_turn()
    {
        // reset temporary turn-by-turn Character stats
        reset_stats();

        // if the Character is inflicted with a status,
        // activate its effect and decrement the number of turns inflicted left
        if (this->status_turns_left != 0) {
            // TODO: call status effect function
            --this->status_turns_left;

            if (this->status_turns_left == 0) {
                this->inflicted_status = CharacterStatus();
            }
        }

        // if the Character has armor active,
        // decrement the number of turns active left
        if (this->armor_turns_left > 0) {
            --this->armor_turns_left;
        }
    }

    void CharacterBattleHandler::perform_action(std::shared_ptr<CharacterBattleHandler> enemy)
    {
        // TODO: call action function
        reset_turn_data();
    }

    void CharacterBattleHandler::reset_stats(bool reset_all)
    {
        this->attack_modifier = 1.0f;
        this->speed_modifier = 1.0f;

        this->protected_from_damage = false;

        this->locked_on_pass = false;
        this->locked_on_weapon = false;
        this->locked_on_special = false;

        this->pass_disabled = false;
        this->weapon_disabled = false;
        this->special_disabled = false;

        if (reset_all) {
            this->current_health = this->base->calculate_health_stat();
            this->armor_turns_left = this->base->get_element().armor_turns;
            this->inflicted_status = CharacterStatus();
            this->status_turns_left = 0;
        }
    }

    void CharacterBattleHandler::reset_turn_data()
    {
        this->ready = false;
        this->selected_action = CharacterActionTypes::PASS;
    }

    bool CharacterBattleHandler::use_item(uint8_t item_index)
    {
        // TODO: call item effect function
        return false;
    }

	void CharacterBattleHandler::obtain_quest_prizes(uint32_t prize_coins,
        uint16_t prize_experience,
        std::vector<uint8_t> prize_items,
        std::vector<uint8_t> prize_weapons)
	{
        this->base->gain_coins(prize_coins);
        this->base->gain_exp(prize_experience);
        
        for (auto prize_item : prize_items) {
            this->base->acquire_item(prize_item);
        }

        for (auto prize_weapon : prize_weapons) {
            this->base->acquire_weapon(prize_weapon);
        }
	}

    void CharacterBattleHandler::select_action(enum CharacterActionTypes action)
    {
        if (this->ready) {
            // if the Character is ready, there is no need to select an action
            return;
        }

        std::bitset<3> disabled_set;
        disabled_set[0] = this->pass_disabled;
        disabled_set[1] = this->weapon_disabled;
        disabled_set[2] = this->special_disabled;
        auto disabled_val = disabled_set.to_ulong();

        // check if the selected action is disabled
        switch (disabled_val) {
        case 0:
            // no actions are disabled
            break;
        case 1:
            // pass disabled
            if (action == CharacterActionTypes::PASS) {
                return;
            }
            break;
        case 2:
            // weapon disabled
            if (action == CharacterActionTypes::WEAPON) {
                return;
            }
            break;
        case 3:
            // pass and weapon disabled
            if ((action == CharacterActionTypes::PASS) || (action == CharacterActionTypes::WEAPON)) {
                return;
            }
            break;
        case 4:
            // special disabled
            if (action == CharacterActionTypes::SPECIAL_ABILITY) {
                return;
            }
            break;
        case 5:
            // pass and special disabled
            if ((action == CharacterActionTypes::PASS) || (action == CharacterActionTypes::SPECIAL_ABILITY)) {
                return;
            }
            break;
        case 6:
            // weapon and special disabled
            if ((action == CharacterActionTypes::WEAPON) || (action == CharacterActionTypes::SPECIAL_ABILITY)) {
                return;
            }
            break;
        }
        // there is no case 7 above because all three actions cannot be disabled at the same time

        // check if the Character is currently locked on an action
        if (this->locked_on_pass) {
            this->selected_action = CharacterActionTypes::PASS;
        }
        else if (this->locked_on_weapon) {
            this->selected_action = CharacterActionTypes::WEAPON;
        }
        else if (this->locked_on_special) {
            this->selected_action = CharacterActionTypes::SPECIAL_ABILITY;
        }
        else {
            this->selected_action = action;
        }

        // signal that the Character is now ready
        this->ready = true;
    }

    void CharacterBattleHandler::register_battle(enum CharacterElements terrain)
    {
        if (this->currently_in_battle) {
            // the Character cannot be in more than one battle at a time
            return;
        }

        this->area_terrain = terrain;
        reset_stats(true);
        this->currently_in_battle = true;
    }
}
