/**
 * CharacterWeapon.h
 * Copyright (c) 2020 Daniel Buckley
 */


#pragma once

#include "CharacterElement.h"
#include "CharacterStatus.h"

namespace le_hero {
	enum class WeaponCategory : uint8_t {
		NO_CATEGORY = 0,
		SLINGSHOT,
		BLADE,
		BOW,
		SPEAR,
		CLUB,
		HAMMER,
		STAFF,
	};

	enum class WeaponHandling : uint8_t {
		ONE_HANDED = 0,
		TWO_HANDED
	};

	enum class WeaponWeight : uint8_t {
		LIGHT = 0,
		MODERATE,
		HEAVY,
	};

	enum class WeaponRange : uint8_t {
		MELEE = 0,
		VARIED,
		LONG,
	};

	enum class WeaponDamageType : uint8_t {
		PHYSICAL = 0,
		MAGICAL,
	};

	typedef struct {
		uint8_t collection_index = 0;
		enum WeaponCategory category = WeaponCategory::NO_CATEGORY;
		enum WeaponHandling handling = WeaponHandling::ONE_HANDED;
		enum WeaponWeight weight = WeaponWeight::LIGHT;
		enum WeaponRange range = WeaponRange::MELEE;
		enum WeaponDamageType damage_type = WeaponDamageType::PHYSICAL;
		std::string name;
		enum CharacterElements element = CharacterElements::BASIC;
		uint8_t strength = 0;
		bool can_inflict_status = false;
		uint8_t inflicted_status = 0;
	} CharacterWeapon;
}