--[[
	quests/quest_rekindled_acquaintances.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Use mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw),
-- mk_enemy_info(e, r, te, wi, sai),
-- and get_weapon_index(e, i) from template script
require 'quests/quest_template'

--Setup quest enemy info
function st_enemy_info()
	enemies = {};
	enemies[0] = mk_enemy_info(0, 0, 128, get_weapon_index(0, 6), 0);
	enemies[1] = mk_enemy_info(1, 0, 128, get_weapon_index(1, 1), 0);
	enemies[2] = mk_enemy_info(3, 0, 162, get_weapon_index(3, 2), 0);
	enemies[3] = mk_enemy_info(3, 0, 200, get_weapon_index(3, 2), 0);
	enemies[4] = mk_enemy_info(3, 0, 264, get_weapon_index(3, 0), 0);
	return enemies
end

-- Setup quest prize items
function st_prize_items()
	items = {};
	items[0] = 29; -- Steel Plate
	items[1] = 30; -- Curing Spell
	items[2] = 31; -- Healing Spell R1
	items[3] = 31; -- Healing Spell R1
	items[4] = 31; -- Healing Spell R1
	items[5] = 0; -- Exp. Spell R1
	items[6] = 0; -- Exp. Spell R1
	return items
end

-- Setup quest prize weapons
function st_prize_weapons()
	weapons = {};
	weapons[0] = get_weapon_index(0, 7); -- Beginner's Elemental Staff
	return weapons
end

-- Construct 'Rekindled Acquaintances' quest
function GetQuest()
	ei = st_enemy_info();
	pi = st_prize_items();
	pw = st_prize_weapons();
	return mk_quest("Wait up! You forgot something!", 5, ei, 23, 1, 100000, 221, 7, pi, 1, pw)
end