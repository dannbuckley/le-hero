--[[
	quests/quest_template.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Create Quest object
function mk_quest(d, ne, ei, rl, qt, pc, pe, npi, pi, npw, pw)
	return {Description=d, NumEnemies=ne, EnemyInfo=ei, RecommendedLevel=rl, QuestTerrain=qt, PrizeCoins=pc, PrizeExp=ep, NumPrizeItems=npi, PrizeItems=pi, NumPrizeWeapons=npw, PrizeWeapons=pw}
end