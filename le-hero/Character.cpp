#include <cmath>
#include "Character.h"

namespace le_hero {
	double Character::_calculate_correction_value(uint8_t _level)
	{
		double alpha = (double)_level / (double)LEVEL_MAX;
		double c = 500.0f;
		c += pow(_level, 1.0 - alpha);
		c /= 10000.0f;
		c += alpha / 8.0f;
		return c; // 0.0506 <= c <= 0.1751 (_level >= 1)
	}

	uint16_t Character::_calculate_attack_stat()
	{
		uint16_t base_attack = this->element.base_attack + this->rank.attack_boost;
		double c = _calculate_correction_value(this->level);
		double final_attack = base_attack;
		final_attack += 50.0f;
		final_attack /= 5.0f;
		final_attack *= this->level;
		return (uint16_t)nearbyint(final_attack * (1.0f - c));
	}

	uint16_t Character::_calculate_speed_stat()
	{
		uint16_t base_speed = this->element.base_speed + this->rank.speed_boost;
		double c = _calculate_correction_value(this->level);
		double final_speed = base_speed;
		final_speed += 50.0f;
		final_speed /= 5.0f;
		final_speed *= this->level;
		return (uint16_t)nearbyint(final_speed * (1.0f - c));
	}

	uint16_t Character::_calculate_health_stat()
	{
		uint16_t base_health = this->element.base_health + this->rank.health_boost;
		double c = _calculate_correction_value(this->level);
		double final_health = base_health;
		final_health += 50.0f;
		final_health /= 5.0f;
		final_health *= this->level;
		return (uint16_t)nearbyint(final_health * (1.0f - c));
	}

	uint16_t Character::_calculate_exp_at_level(uint8_t _level)
	{
		float exp = (float)_level;
		exp = pow(exp, 2);
		exp /= 2.0f;
		exp += (float)_level;
		return (uint16_t)ceilf(exp);
	}

	uint16_t Character::_calculate_exp_to_next_level()
	{
		if (this->total_experience == EXPERIENCE_MAX) {
			return 0;
		}

		float exp_next = this->level + 1.0f;
		exp_next = pow(exp_next, 2);
		exp_next /= 2.0f;
		exp_next += this->level + 1.0f;
		return (uint16_t)ceilf(exp_next) - this->total_experience;
	}

	// Updates the Character's level after gaining experience
	void Character::update_level()
	{
		if (this->total_experience == 0) {
			// min level = 1
			this->level = 1;
		}
		else if (this->total_experience == EXPERIENCE_MAX) {
			this->level = LEVEL_MAX;
		}
		else {
			uint8_t x = this->level;

			// find updated level
			// if the level does not change, the loop ends on the first iteration
			for (uint8_t y = x; y < LEVEL_MAX; y++) {
				uint16_t exp_min, exp_max;
				exp_min = _calculate_exp_at_level(y);
				exp_max = _calculate_exp_at_level(y + 1);

				if (((this->total_experience > exp_min) && (this->total_experience < exp_max)) || (this->total_experience == exp_min)) {
					x = y;
					break;
				}
			}

			// update level
			this->level = x;
		}
	}

	Character::Character(std::shared_ptr<Game> game_env): env(game_env)
	{
		// initialize Weapons Vault, Inventory, and Special Ability Library
		this->vault = std::vector<uint8_t>(env->get_num_weapons());
		this->inventory = std::vector<uint8_t>(env->get_num_items());
		this->library = std::vector<bool>(env->get_num_special_abilities());

		// initialize level to 1
		this->update_level();
	}

	// Adds coin_yield to the Character's amount of coins
	void Character::gain_coins(uint32_t coin_yield)
	{
		// calculate difference between max amount of coins and current amount of coins
		uint32_t diff = COINS_MAX - this->coins;

		// add min(diff, coin_yield) to current amount of coins
		if (diff >= coin_yield) {
			this->coins += coin_yield;
		}
		else {
			this->coins += diff;
		}
	}

	// Adds exp_yield to the Character's total and available experience
	void Character::gain_exp(uint16_t exp_yield)
	{
		// calculate difference between max experience and total experience
		uint16_t diff = EXPERIENCE_MAX - this->total_experience;

		// add min(diff, exp_yield) to total and available experience
		if (diff >= exp_yield) {
			this->total_experience += exp_yield;
			this->available_experience += exp_yield;
		}
		else {
			this->total_experience += diff;
			this->available_experience += diff;
		}

		// update level to reflect gain in experience
		this->update_level();
	}

	// Changes the Character's Special Ability to the ability at index new_spec_abil
	bool Character::change_special_ability(uint8_t new_spec_abil)
	{
		// retrieve Special Ability data from game environment
		CharacterSpecialAbility new_special = env->get_special_ability(new_spec_abil);

		// check if the Character knows the Special Ability and meets its requirements
		if (this->verify_special_ability_requirements(new_special.requirements) && this->library[new_spec_abil]) {
			this->acquired_ability = new_special;
			return true;
		}
		return false;
	}

	// Adds the Special Ability at index new_spec_abil to the Character's library
	bool Character::learn_special_ability(uint8_t new_spec_abil)
	{
		// check if Character already knows the Special Ability
		if (this->library[new_spec_abil]) {
			return true;
		}

		// retrieve Special Ability data from game environment
		CharacterSpecialAbility new_special = env->get_special_ability(new_spec_abil);

		// check if the Character has enough available experience to learn the new Special Ability
		if (new_special.cost_to_learn <= this->available_experience) {
			this->available_experience -= new_special.cost_to_learn;
			this->library[new_spec_abil] = true;
			return true;
		}
		return false;
	}

	// Removes coin_amount from the Character's total amount of coins
	bool Character::spend_coins(uint32_t coin_amount)
	{
		if (coin_amount <= this->coins) {
			this->coins -= coin_amount;
			return true;
		}
		return false;
	}

	// Verifies that the Character is eligible to learn the Special Ability with Requirements reqs
	bool Character::verify_special_ability_requirements(CharacterSpecialAbilityRequirements reqs)
	{
		// check Weapon requirements
		if (reqs.melee_range_weapon_needed || reqs.long_range_weapon_needed) {
			if (reqs.melee_range_weapon_needed) {
				// the character must have a melee or varied range weapon equipped to use this Special Ability
				if (this->weapon.range == WeaponRange::LONG) {
					return false;
				}
			}
			else {
				// the character must have a long or varied range weapon equipped to use this Special Ability
				if (this->weapon.range == WeaponRange::MELEE) {
					return false;
				}
			}
		}

		// check supported Elements
		if (reqs.basic_element_supported
			&& reqs.earth_element_supported
			&& reqs.air_element_supported
			&& reqs.fire_element_supported
			&& reqs.water_element_supported
			&& reqs.mystic_element_supported) {
			// all elements are supported
			return true;
		}
		else {
			// return value associated with Character's element
			switch (this->element.element_identifier) {
			case CharacterElements::BASIC:
				return reqs.basic_element_supported;
			case CharacterElements::EARTH:
				return reqs.earth_element_supported;
			case CharacterElements::AIR:
				return reqs.air_element_supported;
			case CharacterElements::FIRE:
				return reqs.fire_element_supported;
			case CharacterElements::WATER:
				return reqs.water_element_supported;
			case CharacterElements::MYSTIC:
				return reqs.mystic_element_supported;
			default:
				return false;
			}
		}
	}

	// Checks if the Character has the item located at item_index
	bool Character::has_item(uint8_t item_index)
	{
		return this->inventory[item_index] > 0;
	}

	// Checks if the Character is eligible to use the given item
	bool Character::item_availability_level_check(uint8_t item_level)
	{
		return this->level >= item_level;
	}

	// Adds the given item located at item_index to the Character's Inventory
	bool Character::acquire_item(uint8_t item_index)
	{
		if (this->inventory[item_index] < ITEM_AMOUNT_MAX) {
			++this->inventory[item_index];
			return true;
		}
		return false;
	}

	// Buys the item located at item_index and adds it to the Character's inventory
	bool Character::buy_item(uint8_t item_index)
	{
		return false;
	}

	// Removes amount of item located at item_index from the Character's Inventory
	bool Character::remove_item(uint8_t item_index, uint8_t amount)
	{
		if (this->inventory[item_index] >= amount) {
			this->inventory[item_index] -= amount;
			return true;
		}
		return false;
	}
}