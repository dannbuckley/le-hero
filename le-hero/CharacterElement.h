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

	struct CharacterElement {
		std::string name;
		uint8_t armor_percent = 0;
		uint8_t armor_turns = 0;
		uint8_t base_attack = 0;
		uint8_t base_speed = 0;
		uint8_t base_health = 0;
		enum CharacterElements element_identifier = CharacterElements::BASIC;
	};
}