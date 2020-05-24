--[[
	quests/quest_onward_young_hero.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Use mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw),
-- mk_enemy_info(e, r, te, wi, sai),
-- and get_weapon_index(e, i) from template script
require 'quests/quest_template'

-- Setup quest enemy info
function st_enemy_info()
	enemies = {};
	enemies[0] = mk_enemy_info(0, 0, 4, get_weapon_index(0, 0), 0);
	enemies[1] = mk_enemy_info(0, 0, 4, get_weapon_index(0, 3), 0);
	enemies[2] = mk_enemy_info(0, 0, 4, get_weapon_index(0, 3), 0);
	enemies[3] = mk_enemy_info(0, 0, 12, get_weapon_index(0, 2), 0);
	return enemies
end

-- Setup quest prize items
function st_prize_items()
	items = {};
	items[0] = 0; -- Exp. Spell R1
	items[1] = 31; -- Healing Spell R1
	items[2] = 31; -- Healing Spell R1
	return items
end

-- Setup quest prize weapons
function st_prize_weapons()
	weapons = {};
	weapons[0] = get_weapon_index(0, 0); -- Slingshot
	weapons[1] = get_weapon_index(0, 1); -- Sword
	return weapons
end

-- Construct 'Onward Young Hero!' quest
function GetQuest()
	ei = st_enemy_info();
	pi = st_prize_items();
	pw = st_prize_weapons();
	return mk_quest("The beginning of a very long journey.", 4, ei, 5, 0, 80000, 6, 3, pi, 2, pw)
end