--[[
	quests/quest_onward_young_hero.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Use mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw) from template script
require 'quests/quest_template'

-- Setup quest enemy info
function st_enemy_info()
	return {}
end

-- Setup quest prize items
function st_prize_items()
	return {}
end

-- Setup quest prize weapons
function st_prize_weapons()
	return {}
end

-- Construct 'Onward Young Hero!' quest
function GetQuest()
	return mk_quest("", 4, {}, 0, 0, 0, 0, 3, {}, 2, {})
end