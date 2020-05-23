--[[
	quests/index.lua
	Copyright (c) 2020 Daniel Buckley
--]]

num_quests = 7

function mk_quest_ref(n, qn)
	return {QuestFile="quests/quest_"..n..".lua", QuestName=qn}
end

quests = {}
quests[0] = mk_quest_ref("onward_young_hero", "Onward Young Hero!")
quests[1] = mk_quest_ref("into_the_depths", "Into the Depths")
quests[2] = mk_quest_ref("out_of_the_frying_pan", "Out of the Frying Pan")
quests[3] = mk_quest_ref("the_not_so_stealthy_escape", "The Not-so-Stealthy Escape")
quests[4] = mk_quest_ref("soaring_through_the_night", "Soaring Through the Night")
quests[5] = mk_quest_ref("through_the_swampy_marsh", "Through the Swampy Marsh")
quests[6] = mk_quest_ref("the_first_of_many", "The First of Many")

function GetQuestRef(n)
	return quests[n]
end