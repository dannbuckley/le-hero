--[[
	quests/quest_through_the_swampy_marsh.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Use mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw),
-- mk_enemy_info(e, r, te, wi, sai),
-- and get_weapon_index(e, i) from template script
require 'quests/quest_template'

--Setup quest enemy info
function st_enemy_info()
	enemies = {};
	enemies[0] = mk_enemy_info(0, 0, 60, get_weapon_index(0, 5), 0);
	enemies[1] = mk_enemy_info(0, 0, 84, get_weapon_index(0, 6), 0);
	enemies[2] = mk_enemy_info(1, 0, 98, get_weapon_index(1, 1), 0);
	enemies[3] = mk_enemy_info(4, 0, 128, get_weapon_index(4, 1), 0);
	enemies[4] = mk_enemy_info(4, 0, 144, get_weapon_index(4, 0), 0);
	return enemies
end

-- Setup quest prize items
function st_prize_items()
	items = {};
	items[0] = 30; -- Curing Spell
	items[1] = 30; -- Curing Spell
	items[2] = 31; -- Healing Spell R1
	items[3] = 31; -- Healing Spell R1
	return items
end

-- Setup quest prize weapons
function st_prize_weapons()
	weapons = {};
	weapons[0] = get_weapon_index(0, 6); -- Cursed Blade
	return weapons
end

-- Construct 'Through the Swampy Marsh' quest
function GetQuest()
	ei = st_enemy_info();
	pi = st_prize_items();
	pw = st_prize_weapons();
	return mk_quest("Ugh! Is this really the only way through?!", 5, ei, 17, 4, 100000, 129, 4, pi, 1, pw)
end