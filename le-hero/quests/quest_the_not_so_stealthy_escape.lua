--[[
	quests/quest_the_not_so_stealthy_escape.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Use mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw),
-- mk_enemy_info(e, r, te, wi, sai),
-- and get_weapon_index(e, i) from template script
require 'quests/quest_template'

--Setup quest enemy info
function st_enemy_info()
	enemies = {};
	enemies[0] = mk_enemy_info(0, 0, 40, get_weapon_index(0, 4), 0);
	enemies[1] = mk_enemy_info(0, 0, 32, get_weapon_index(0, 5), 1);
	enemies[2] = mk_enemy_info(4, 0, 32, get_weapon_index(4, 0), 1);
	enemies[3] = mk_enemy_info(4, 0, 24, get_weapon_index(4, 0), 0);
	enemies[4] = mk_enemy_info(4, 0, 50, get_weapon_index(0, 6), 0);
	return enemies
end

-- Setup quest prize items
function st_prize_items()
	items = {};
	items[0] = 31; -- Healing Spell R1
	items[1] = 31; -- Healing Spell R1
	return items
end

-- Setup quest prize weapons
function st_prize_weapons()
	weapons = {};
	weapons[0] = get_weapon_index(4, 0); -- Tattered Sea Serpent Bow
	weapons[1] = get_weapon_index(0, 4); -- Katana
	return weapons
end

-- Construct 'The Not-so-Stealthy Escape' quest
function GetQuest()
	ei = st_enemy_info();
	pi = st_prize_items();
	pw = st_prize_weapons();
	return mk_quest("When all you wanted to do was go for a swim...", 5, ei, 10, 4, 100000, 45, 2, pi, 2, pw)
end