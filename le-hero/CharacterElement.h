/**
 * CharacterElement.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <cstdint>
#include <string>

namespace le_hero {
	enum class CharacterElements : uint8_t {
		BASIC = 0,
		EARTH,
		AIR,
		FIRE,
		WATER,
		MYSTIC,
		ALPHA,
	};

	typedef struct {
		std::string name;
		uint8_t armor_percent;
		uint8_t armor_turns;
		uint8_t base_attack;
		uint8_t base_speed;
		uint8_t base_health;
	} CharacterElement;
}