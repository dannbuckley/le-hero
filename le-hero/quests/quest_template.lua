--[[
	quests/quest_template.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Create Quest object
function mk_quest(d, qt, ne, ei)
	return {Description=d, QuestTerrain=qt, NumEnemies=ne, EnemyInfo=ei}
end

-- Create Enemy Info object
function mk_enemy_info(e, r, te, wi, sai)
	return {Element=e, Rank=r, TotalExperience=te, WeaponIndex=wi, SpecialAbilIndex=sai}
end

-- Convert Element and Index to Weapon Index
function get_weapon_index(e, i)
	return (e * 8) + i
end