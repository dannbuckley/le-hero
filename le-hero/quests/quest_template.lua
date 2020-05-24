--[[
	quests/quest_template.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Create Quest object
function mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw)
	return {Description=d, NumEnemies=ne, EnemyInfo=ei, RecommendedLevel=rl, QuestTerrain=qt, PrizeCoins=pc, PrizeExp=pe, NumPrizeItems=npi, PrizeItems=pi, NumPrizeWeapons=npw, PrizeWeapons=pw}
end

-- Create Enemy Info object
function mk_enemy_info(e, r, te, wi, sai)
	return {Element=e, Rank=r, TotalExperience=te, WeaponIndex=wi, SpecialAbilIndex=sai}
end

-- Convert Element and Index to Weapon Index
function get_weapon_index(e, i)
	return (e * 8) + i
end