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
		uint8_t collection_index;
		enum WeaponCategory category;
		enum WeaponHandling handling;
		enum WeaponWeight weight;
		enum WeaponRange range;
		enum WeaponDamageType damage_type;
		std::string name;
		enum CharacterElements element;
		uint8_t strength;
		bool can_inflict_status;
		uint8_t inflicted_status;
	} CharacterWeapon;
}