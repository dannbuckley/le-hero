--[[
	quests/quest_out_of_the_frying_pan.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Use mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw),
-- mk_enemy_info(e, r, te, wi, sai),
-- and get_weapon_index(e, i) from template script
require 'quests/quest_template'

--Setup quest enemy info
function st_enemy_info()
	enemies = {};
	enemies[0] = mk_enemy_info(0, 0, 18, get_weapon_index(0, 1), 1);
	enemies[1] = mk_enemy_info(1, 0, 8, get_weapon_index(1, 0), 0);
	enemies[2] = mk_enemy_info(3, 0, 12, get_weapon_index(3, 0), 1);
	enemies[3] = mk_enemy_info(3, 0, 8, get_weapon_index(3, 0), 0);
	enemies[4] = mk_enemy_info(3, 0, 24, get_weapon_index(0, 4), 0);
	return enemies
end

-- Setup quest prize items
function st_prize_items()
	items = {};
	items[0] = 29; -- Steel Plate
	items[1] = 31; -- Healing Spell R1
	return items
end

-- Setup quest prize weapons
function st_prize_weapons()
	weapons = {};
	weapons[0] = get_weapon_index(3, 0); -- Dull Dragon Sword
	weapons[1] = get_weapon_index(0, 3); -- Dagger
	return weapons
end

-- Construct 'Out of the Frying Pan' quest
function GetQuest()
	ei = st_enemy_info();
	pi = st_prize_items();
	pw = st_prize_weapons();
	return mk_quest("From danger, to danger.", 5, ei, 7, 3, 100000, 21, 2, pi, 2, pw)
end