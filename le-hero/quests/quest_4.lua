--[[
  quests/quest_4.lua
  Copyright (c) 2020 Daniel Buckley
--]]

-- Use mk_quest(d, qt, ne, ei),
-- mk_enemy_info(e, r, te, wi, sai),
-- and get_weapon_index(e, i) from template script
require 'quests/quest_template'

-- Setup quest enemy info
function st_enemy_info()
  enemies = {};
  return enemies
end

-- Construct quest object
function GetQuest()
  ei = st_enemy_info();
  return mk_quest("", 0, 0, ei)
end