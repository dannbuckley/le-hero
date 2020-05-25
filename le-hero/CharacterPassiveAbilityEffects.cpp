/**
 * CharacterPassiveAbilityEffects.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include <cmath>
#include "CharacterPassiveAbilityEffects.h"

namespace le_hero {
	namespace effect {
		bool activate_passive_ability_effect(std::shared_ptr<CharacterBattleHandler> self)
		{
			using namespace passive_ability;

			auto p_abil = self->get_passive_ability();

			switch (p_abil.native_element) {
			case CharacterElements::BASIC:
				return CharacterPassiveAbilityEffects::basic_passive_effect(self);
			case CharacterElements::EARTH:
				return CharacterPassiveAbilityEffects::earth_passive_effect(self);
			case CharacterElements::AIR:
				return CharacterPassiveAbilityEffects::air_passive_effect(self);
			case CharacterElements::FIRE:
				return CharacterPassiveAbilityEffects::fire_passive_effect(self);
			case CharacterElements::WATER:
				return CharacterPassiveAbilityEffects::water_passive_effect(self);
			case CharacterElements::MYSTIC:
				return CharacterPassiveAbilityEffects::mystic_passive_effect(self);
			case CharacterElements::ALPHA:
				return CharacterPassiveAbilityEffects::alpha_passive_effect(self);
			default:
				// not a valid passive ability
				return false;
			}
		}

		namespace passive_ability {
			bool CharacterPassiveAbilityEffects::basic_passive_effect(std::shared_ptr<CharacterBattleHandler> self)
			{
				uint16_t max_health = self->get_maximum_health();
				if (self->get_current_health() < (uint16_t)ceilf(max_health / 2.0f)) {
					// double attack if current health is at less then 50%
					self->apply_attack_modifier(2.0f);
					return true;
				}

				// return false if ability has no effect
				return false;
			}

			bool CharacterPassiveAbilityEffects::earth_passive_effect(std::shared_ptr<CharacterBattleHandler> self)
			{
				auto terrain = self->get_area_terrain();
				auto current_weapon = self->get_equipped_weapon();
				auto selected_action = self->get_selected_action();
				if ((terrain == CharacterElements::EARTH)
					&& (current_weapon.range == WeaponRange::MELEE)
					&& (selected_action == CharacterActionTypes::WEAPON)) {
					// boost attack by 30% if the above conditions are met
					self->apply_attack_modifier(1.3f);
					return true;
				}

				// return false if ability has no effect
				return false;
			}

			bool CharacterPassiveAbilityEffects::air_passive_effect(std::shared_ptr<CharacterBattleHandler> self)
			{
				auto terrain = self->get_area_terrain();
				auto current_weapon = self->get_equipped_weapon();
				auto selected_action = self->get_selected_action();
				if ((terrain == CharacterElements::AIR)
					&& (current_weapon.range == WeaponRange::LONG)
					&& (selected_action == CharacterActionTypes::WEAPON)) {
					// boost attack by 30% if the above conditions are met
					self->apply_attack_modifier(1.3f);
					return true;
				}

				// return false if ability has no effect
				return false;
			}

			bool CharacterPassiveAbilityEffects::fire_passive_effect(std::shared_ptr<CharacterBattleHandler> self)
			{
				if (self->get_area_terrain() == CharacterElements::FIRE) {
					// boost attack by 10% if the area terrain matches the Character's element
					self->apply_attack_modifier(1.1f);
					return true;
				}

				// return false if ability has no effect
				return false;
			}

			bool CharacterPassiveAbilityEffects::water_passive_effect(std::shared_ptr<CharacterBattleHandler> self)
			{
				if (self->get_area_terrain() == CharacterElements::WATER) {
					// boost speed by 10% if the area terrain matches the Character's element
					self->apply_speed_modifier(1.1f);
					return true;
				}

				// return false if ability has no effect
				return false;
			}

			bool CharacterPassiveAbilityEffects::mystic_passive_effect(std::shared_ptr<CharacterBattleHandler> self)
			{
				// currently no effect for mystic passive ability
				return false;
			}

			bool CharacterPassiveAbilityEffects::alpha_passive_effect(std::shared_ptr<CharacterBattleHandler> self)
			{
				uint16_t max_health = self->get_maximum_health();
				if (self->get_current_health() <= (uint16_t)floorf(max_health * 0.15f)) {
					// if current health is at or below 15%, attempt to self-inflict the Enlightened status
					bool result = self->inflict_status(2);
					return result;
				}

				// return false if ability has no effect
				return false;
			}
		}
	}
}