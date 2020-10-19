--[[
	quests/index.lua
	Copyright (c) 2020 Daniel Buckley
--]]

num_quests = 22

function mk_quest_ref(n, qn)
	return {QuestFile="quests/quest_"..n..".lua", QuestName=qn}
end

quests = {}
quests[0] = mk_quest_ref("1", "Quest 1")
quests[1] = mk_quest_ref("2", "Quest 2")
quests[2] = mk_quest_ref("3", "Quest 3")
quests[3] = mk_quest_ref("4", "Quest 4")
quests[4] = mk_quest_ref("5a", "Quest 5a")
quests[5] = mk_quest_ref("6a", "Quest 6a")
quests[6] = mk_quest_ref("7a", "Quest 7a")
quests[7] = mk_quest_ref("8a", "Quest 8a")
quests[8] = mk_quest_ref("9a", "Quest 9a")
quests[9] = mk_quest_ref("10a", "Quest 10a")
quests[10] = mk_quest_ref("5b", "Quest 5b")
quests[11] = mk_quest_ref("6b", "Quest 6b")
quests[12] = mk_quest_ref("7b", "Quest 7b")
quests[13] = mk_quest_ref("8b", "Quest 8b")
quests[14] = mk_quest_ref("9b", "Quest 9b")
quests[15] = mk_quest_ref("10b", "Quest 10b")
quests[16] = mk_quest_ref("11", "Quest 11")
quests[17] = mk_quest_ref("12", "Quest 12")
quests[18] = mk_quest_ref("13a", "Quest 13a")
quests[19] = mk_quest_ref("13b", "Quest 13b")
quests[20] = mk_quest_ref("14", "Quest 14")
quests[21] = mk_quest_ref("15", "Quest 15")

function GetQuestRef(n)
	return quests[n]
end