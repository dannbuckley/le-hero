--[[
	quests/quest_the_first_of_many.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Use mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw),
-- mk_enemy_info(e, r, te, wi, sai),
-- and get_weapon_index(e, i) from template script
require 'quests/quest_template'

--Setup quest enemy info
function st_enemy_info()
	enemies = {};
	enemies[0] = mk_enemy_info(0, 0, 220, get_weapon_index(0, 7), 0);
	enemies[1] = mk_enemy_info(2, 0, 220, get_weapon_index(2, 0), 0);
	enemies[2] = mk_enemy_info(1, 0, 220, get_weapon_index(1, 0), 0);
	enemies[3] = mk_enemy_info(3, 0, 220, get_weapon_index(3, 0), 0);
	enemies[4] = mk_enemy_info(4, 0, 220, get_weapon_index(4, 0), 0);
	enemies[5] = mk_enemy_info(6, 0, 288, get_weapon_index(6, 0), 0);
	return enemies
end

-- Setup quest prize items
function st_prize_items()
	items = {};
	items[0] = 29; -- Steel Plate
	items[1] = 30; -- Curing Spell
	items[2] = 30; -- Curing Spell
	items[3] = 32; -- Healing Spell R2
	items[4] = 1; -- Exp. Spell R2
	return items
end

-- Setup quest prize weapons
function st_prize_weapons()
	weapons = {};
	weapons[0] = get_weapon_index(6, 0); -- Staff of Simplicity
	return weapons
end

-- Construct 'The First of Many' quest
function GetQuest()
	ei = st_enemy_info();
	pi = st_prize_items();
	pw = st_prize_weapons();
	return mk_quest("Prepare yourself, for you face the first of many trials!", 6, ei, 31, 6, 120000, 347, 5, pi, 1, pw)
end