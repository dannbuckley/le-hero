/**
 * CharacterStatus.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <cstdint>
#include <string>

namespace le_hero {
	enum class CharacterStatusTypes : uint8_t {
		HEALTH_INFLUENCE = 0,
		ATTACK_INFLUENCE,
		ARMOR_INFLUENCE,
		MULTI_INFLUENCE,
	};

	struct CharacterStatus {
		uint8_t index = 0;
		std::string name;
		std::string effect;
		uint8_t effect_length = 0;
		enum CharacterStatusTypes status_type = CharacterStatusTypes::HEALTH_INFLUENCE;
	};
}