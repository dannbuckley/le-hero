/**
 * CharacterRank.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <cstdint>
#include <string>

namespace le_hero {
	enum class CharacterRanks : uint8_t {
		F = 0,
		E,
		D,
		C,
		B,
		A,
		Z,
	};

	typedef struct {
		std::string name;
		uint8_t attack_boost = 0;
		uint8_t speed_boost = 0;
		uint8_t health_boost = 0;
	} CharacterRank;
}