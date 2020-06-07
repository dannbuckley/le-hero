/**
 * CharacterBattleHandler.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <bitset>
#include <cmath>
#include "CharacterBattleHandler.h"
#include "CharacterEffectFunctions.h"

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

	uint8_t CharacterBattleHandler::get_base_level()
	{
		return this->base->get_level();
	}

    uint16_t CharacterBattleHandler::get_base_exp_to_next_level()
    {
        return this->base->calculate_exp_to_next_level();
    }

    uint16_t CharacterBattleHandler::get_base_exp()
    {
        return this->base->get_experience();
    }

	const CharacterPassiveAbility& CharacterBattleHandler::get_passive_ability() const
    {
        return this->base->get_passive_ability();
    }

    const CharacterWeapon& CharacterBattleHandler::get_equipped_weapon() const
    {
        return this->base->get_equipped_weapon();
    }

    const CharacterSpecialAbility& CharacterBattleHandler::get_special_ability() const
    {
        return this->base->get_special_ability();
    }

    void CharacterBattleHandler::base_gain_exp(uint16_t yield)
    {
        this->base->gain_exp(yield);
    }

    void CharacterBattleHandler::base_gain_coins(uint32_t yield)
    {
        this->base->gain_coins(yield);
    }

	bool CharacterBattleHandler::is_ready()
	{
		return this->ready;
	}

    bool CharacterBattleHandler::is_in_battle()
    {
        return this->currently_in_battle;
    }

    enum CharacterActionTypes CharacterBattleHandler::get_selected_action()
    {
        return this->selected_action;
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

    bool CharacterBattleHandler::inflict_status(uint8_t new_status)
    {
        // check if the Character is already inflicted with a status
        if (this->status_turns_left != 0) {
            return false;
        }

        // get status data from game environment
        auto new_status_data = game::get_status(new_status);

        // inflict the Character with the provided status
        this->inflicted_status = new_status_data;
        this->status_turns_left = new_status_data.effect_length;
        return false;
    }

    CharacterStatus CharacterBattleHandler::get_inflicted_status()
    {
        return this->inflicted_status;
    }

    uint8_t CharacterBattleHandler::get_status_turns_left()
    {
        return this->status_turns_left;
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

    void CharacterBattleHandler::remove_armor()
    {
        this->armor_turns_left = 0;
    }

    uint8_t CharacterBattleHandler::get_armor_turns_left()
    {
        return this->armor_turns_left;
    }

    void CharacterBattleHandler::protect_from_damage()
    {
        this->protected_from_damage = true;
    }

    uint16_t CharacterBattleHandler::get_base_attack_stat()
    {
        return this->base->calculate_attack_stat();
    }

    uint16_t CharacterBattleHandler::get_base_speed_stat()
    {
        return this->base->calculate_speed_stat();
    }

    uint16_t CharacterBattleHandler::calculate_battle_attack_stat()
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

	uint16_t CharacterBattleHandler::get_maximum_health()
	{
		return this->base->calculate_health_stat();
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

    enum CharacterElements CharacterBattleHandler::get_area_terrain()
    {
        return this->area_terrain;
    }

	void CharacterBattleHandler::apply_attack_modifier(float mod)
	{
        this->attack_modifier *= mod;
	}

    void CharacterBattleHandler::apply_speed_modifier(float mod)
    {
        this->speed_modifier *= mod;
    }

	void CharacterBattleHandler::lock_on_pass()
	{
        this->locked_on_pass = true;
	}

    void CharacterBattleHandler::lock_on_weapon()
    {
        this->locked_on_weapon = true;
    }

    void CharacterBattleHandler::lock_on_special()
    {
        this->locked_on_special = true;
    }

    void CharacterBattleHandler::disable_pass()
    {
        this->pass_disabled = true;
    }

    void CharacterBattleHandler::disable_weapon()
    {
        this->weapon_disabled = true;
    }

    void CharacterBattleHandler::disable_special()
    {
        this->special_disabled = true;
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
            effect::activate_status_effect(this);
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
            this->damage_dealt = 0;
        }
    }

    void CharacterBattleHandler::reset_turn_data()
    {
        this->ready = false;
        this->selected_action = CharacterActionTypes::PASS;
    }

    bool CharacterBattleHandler::use_item(uint8_t item_index)
    {
        if (effect::activate_item_effect(item_index, this)) {
            this->base->remove_item(item_index, 1);
            return true;
        }

        // return false if item has no effect
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

    void CharacterBattleHandler::register_damage_dealt(uint16_t damage)
    {
        this->damage_dealt = damage;
    }
    uint16_t CharacterBattleHandler::get_damage_dealt()
    {
        return this->damage_dealt;
    }
}