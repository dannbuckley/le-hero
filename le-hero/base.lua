--[[
	base.lua
	Copyright (c) 2020 Daniel Buckley
--]]

-- Reference to quests index file
quests_index_file = "quests/index.lua"

-- Define character elements
function mk_element(n, ap, at, ba, bs, bh)
	return {Name=n, ArmorPercent=ap, ArmorTurns=at, BaseAttack=ba, BaseSpeed=bs, BaseHealth=bh}
end

elements = {}
elements[0] = mk_element("Basic", 15, 50, 13, 13, 28)
elements[1] = mk_element("Earth", 35, 60, 22, 14, 70)
elements[2] = mk_element("Air", 30, 60, 17, 22, 49)
elements[3] = mk_element("Fire", 30, 60, 17, 17, 62)
elements[4] = mk_element("Water", 35, 60, 14, 20, 56)
elements[5] = mk_element("Mystic", 50, 150, 26, 26, 78)
elements[6] = mk_element("Alpha", 40, 25, 29, 29, 84)

-- Define character ranks
function mk_rank(n, ab, sb, hb)
	return {Name=n, AttackBoost=ab, SpeedBoost=sb, HealthBoost=hb}
end

ranks = {}
ranks[0] = mk_rank("F", 0, 0, 0)
ranks[1] = mk_rank("E", 3, 3, 8)
ranks[2] = mk_rank("D", 8, 8, 10)
ranks[3] = mk_rank("C", 15, 15, 15)
ranks[4] = mk_rank("B", 30, 30, 25)
ranks[5] = mk_rank("A", 45, 45, 40)
ranks[6] = mk_rank("Z", 60, 60, 50)

-- Define character statuses
function mk_status(n, e, el, st)
	return {Name=n, Effect=e, EffectLength=el, StatusType=st}
end

num_statuses = 14
statuses = {}
statuses[0] = mk_status("Burn", "Damages character 1% of their maximum health every turn for 15 turns.", 15, 0)
statuses[1] = mk_status("Poison", "Damages character 3% of their maximum health every turn for 15 turns.", 15, 0)
statuses[2] = mk_status("Enlightened", "The character becomes enlightened, and can heal itself for 5 turns.", 5, 0)
statuses[3] = mk_status("Guarding", "The character is protected from any damage for 3 turns.", 3, 0)
statuses[4] = mk_status("Mystified", "The character becomes mystified by its enemy and cannot attack.", 5, 1)
statuses[5] = mk_status("Enraged", "The character becomes enraged and is forced to attack only with its weapon.", 5, 1)
statuses[6] = mk_status("Weightless", "The user becomes weightless and floats up, making it impossible to use close-range weapons.", 1, 1)
statuses[7] = mk_status("Claustrophobic", "The character is trapped in a tight space, making it impossible to use long-range weapons.", 1, 1)
statuses[8] = mk_status("Frozen", "The character is trapped in ice and is forced to pass its turn.", 5, 1)
statuses[9] = mk_status("Amnesiac", "The character has temporary amnesia, and cannot remember how to use its special ability.", 1, 1)
statuses[10] = mk_status("Shattered Armor", "Removes the effect of armor from the character.", 1, 2)
statuses[11] = mk_status("Unworthy", "This character is deemed unworthy by its enemy. It is damaged by 50% of its maximum health, removed of armor, and forced to pass its turn.", 1, 3)
statuses[12] = mk_status("Protecting", "The character is protected from any damage for 1 turn.", 1, 3)
statuses[13] = mk_status("Frenzy", "Raises the characters attack and speed by 80% and heals for 40% of damage dealt with a weapon in the previous turn.", 0, 3)

-- Define weapons
function mk_weapon(ci, c, h, w, r, dt, n, e, str, cis, is)
	return {CollectionIndex=ci, Category=c, Handling=h, Weight=w, Range=r, DamageType=dt, Name=n, Element=e, Strength=str, CanInflictStatus=cis, InflictedStatus=is}
end

num_weapons = 56
weapons = {}
-- Basic Weapons
weapons[0] = mk_weapon(0, 1, 1, 0, 1, 0, "Slingshot", 0, 10, false, 0)
weapons[1] = mk_weapon(1, 2, 0, 1, 0, 0, "Sword", 0, 23, false, 0)
weapons[2] = mk_weapon(2, 3, 1, 0, 2, 0, "Bow", 0, 18, false, 0)
weapons[3] = mk_weapon(3, 2, 0, 0, 0, 0, "Dagger", 0, 15, false, 0)
weapons[4] = mk_weapon(4, 2, 1, 2, 0, 0, "Katana", 0, 25, false, 0)
weapons[5] = mk_weapon(5, 4, 1, 0, 1, 0, "Javelin", 0, 27, false, 0)
weapons[6] = mk_weapon(6, 2, 1, 1, 0, 1, "Cursed Blade", 0, 35, false, 0)
weapons[7] = mk_weapon(7, 7, 1, 0, 1, 1, "Beginner's Elemental Staff", 0, 37, true, 4)

-- Earth Weapons
weapons[8] = mk_weapon(0, 2, 0, 1, 0, 0, "Dull Wolf Katana", 1, 45, false, 0)
weapons[9] = mk_weapon(1, 4, 1, 1, 1, 0, "Ancient Spear", 1, 49, true, 1)
weapons[10] = mk_weapon(2, 5, 0, 1, 0, 0, "Bone Club", 1, 54, false, 0)
weapons[11] = mk_weapon(3, 3, 1, 0, 1, 0, "Marksman's Crossbow", 1, 60, false, 0)
weapons[12] = mk_weapon(4, 2, 1, 1, 0, 0, "Earthen Scythe", 1, 67, true, 7)
weapons[13] = mk_weapon(5, 2, 1, 2, 0, 0, "Tungsten Katana", 1, 71, false, 0)
weapons[14] = mk_weapon(6, 7, 1, 0, 1, 1, "Staff of the Wolf's Eye", 1, 75, false, 0)
weapons[15] = mk_weapon(7, 2, 1, 2, 0, 0, "Wolf's Eye Katana", 1, 80, true, 4)

-- Air Weapons
weapons[16] = mk_weapon(0, 3, 0, 0, 0, 0, "Tattered Eagle Bow", 2, 45, true, 6)
weapons[17] = mk_weapon(1, 2, 0, 0, 0, 0, "Sky Blade", 2, 51, false, 0)
weapons[18] = mk_weapon(2, 1, 1, 0, 1, 0, "Reinforced Slingshot", 2, 56, false, 0)
weapons[19] = mk_weapon(3, 3, 1, 1, 2, 1, "Poisoned Bow", 2, 60, true, 1)
weapons[20] = mk_weapon(4, 2, 0, 0, 0, 0, "Lightening Sword", 2, 64, true, 6)
weapons[21] = mk_weapon(5, 4, 1, 1, 1, 1, "Spear of Shattering", 2, 69, true, 10)
weapons[22] = mk_weapon(6, 7, 1, 0, 1, 1, "Staff of the Eagle's Talon", 2, 75, false, 0)
weapons[23] = mk_weapon(7, 3, 1, 2, 2, 0, "Spirit Eagle Bow", 2, 80, true, 4)

-- Fire Weapons
weapons[24] = mk_weapon(0, 2, 0, 0, 0, 0, "Dull Dragon Sword", 3, 45, true, 0)
weapons[25] = mk_weapon(1, 3, 1, 0, 2, 0, "Flaming Bow", 3, 53, true, 0)
weapons[26] = mk_weapon(2, 2, 0, 0, 0, 0, "Scorching Dagger", 3, 49, true, 0)
weapons[27] = mk_weapon(3, 2, 0, 1, 0, 0, "Volcanic Sword", 3, 57, true, 0)
weapons[28] = mk_weapon(4, 2, 0, 2, 0, 0, "Infernal Axe", 3, 68, false, 0)
weapons[29] = mk_weapon(5, 6, 1, 2, 0, 0, "Lava Hammer", 3, 72, false, 0)
weapons[30] = mk_weapon(6, 7, 1, 0, 1, 1, "Staff of the Dragon's Horn", 3, 75, false, 0)
weapons[31] = mk_weapon(7, 2, 1, 1, 0, 0, "Dragon Claw Sword", 3, 80, true, 4)

-- Water Weapons
weapons[32] = mk_weapon(0, 3, 1, 0, 2, 0, "Tattered Sea Serpent Bow", 4, 45, false, 0)
weapons[33] = mk_weapon(1, 2, 1, 1, 0, 0, "Ice Scimitar", 4, 50, false, 0)
weapons[34] = mk_weapon(2, 3, 1, 0, 2, 0, "Frozen Bow", 4, 53, true, 8)
weapons[35] = mk_weapon(3, 4, 1, 0, 0, 0, "Icicle Spear", 4, 61, false, 0)
weapons[36] = mk_weapon(4, 2, 0, 0, 0, 0, "Coral Bayonet", 4, 66, false, 0)
weapons[37] = mk_weapon(5, 5, 0, 2, 0, 1, "Subzero Mace", 4, 71, true, 8)
weapons[38] = mk_weapon(6, 7, 1, 0, 1, 1, "Staff of the Serpent's Fang", 4, 75, false, 0)
weapons[39] = mk_weapon(7, 3, 1, 0, 2, 0, "Sea Serpent Bow", 4, 80, true, 4)

-- Mystic Weapons
weapons[40] = mk_weapon(0, 0, 0, 0, 0, 0, "", 5, 45, false, 0)
weapons[41] = mk_weapon(1, 0, 0, 0, 0, 0, "", 5, 50, false, 0)
weapons[42] = mk_weapon(2, 0, 0, 0, 0, 0, "", 5, 55, false, 0)
weapons[43] = mk_weapon(3, 0, 0, 0, 0, 0, "", 5, 60, false, 0)
weapons[44] = mk_weapon(4, 0, 0, 0, 0, 0, "", 5, 65, false, 0)
weapons[45] = mk_weapon(5, 0, 0, 0, 0, 0, "", 5, 70, false, 0)
weapons[46] = mk_weapon(6, 7, 0, 0, 0, 0, "Elemental Staff", 5, 75, false, 0)
weapons[47] = mk_weapon(7, 0, 0, 0, 0, 0, "", 5, 80, true, 4)

-- Alpha Weapons
weapons[48] = mk_weapon(0, 7, 1, 0, 1, 1, "Staff of Simplicity", 6, 85, false, 0)
weapons[49] = mk_weapon(1, 7, 1, 1, 1, 1, "Staff of Sky", 6, 90, true, 6)
weapons[50] = mk_weapon(2, 7, 1, 1, 1, 1, "Staff of Land", 6, 90, true, 7)
weapons[51] = mk_weapon(3, 7, 1, 1, 1, 1, "Staff of Flame", 6, 90, true, 0)
weapons[52] = mk_weapon(4, 7, 1, 1, 1, 1, "Staff of Sea", 6, 90, false, 0)
weapons[53] = mk_weapon(5, 7, 1, 1, 1, 1, "Staff of Mastery", 6, 90, false, 0)
weapons[54] = mk_weapon(6, 7, 1, 1, 1, 1, "Staff of Rage", 6, 95, true, 5)
weapons[55] = mk_weapon(7, 7, 1, 2, 1, 1, "Staff of Creation", 6, 100, true, 11)

-- Define passive abilities
function mk_passive_ability(n, e)
	return {Name=n, Effect=e}
end

passive_abilities = {}
-- Basic
passive_abilities[0] = mk_passive_ability("Firm Resolve", "When Health drops below 50%, the Attack stat is doubled.")
-- Earth
passive_abilities[1] = mk_passive_ability("Fighter", "Power of close-range attacks increase by 30% when battling in Earth terrain.")
-- Air
passive_abilities[2] = mk_passive_ability("Sniper", "Power of long-range attacks increase by 30% when battling in Air terrain.")
-- Fire
passive_abilities[3] = mk_passive_ability("Temper", "Attack is increased by 10% when battling in Fire terrain.")
-- Water
passive_abilities[4] = mk_passive_ability("Swift Swimmer", "Speed is increased by 10% when battling in Water terrain.")
-- Mystic
passive_abilities[5] = mk_passive_ability("Passive - Mystic", "")
-- Alpha
passive_abilities[6] = mk_passive_ability("Divine Nature", "When Health drops to 15%, the Character gains the Enlightened status.")

-- Define special abilties
function mk_special_ability(n, e, c, w, el)
	return {Name=n, Effect=e, CostToLearn=c, WeaponReqs=w, ElementSupport=el}
end

num_special_abilities = 19
special_abilities = {}
special_abilities[0] = mk_special_ability("Protect", "Protects character from any damage.", 0, 0, 63)
special_abilities[1] = mk_special_ability("Recovery", "Recover 25% of maximum health.", 0, 0, 63)
special_abilities[2] = mk_special_ability("Tricky Mirror", "Transfers the current inflicted status (if one) to the enemy.", 0, 0, 63)
special_abilities[3] = mk_special_ability("Revenge", "The lower the user's current health is, the greater the damage.", 0, 0, 63)
special_abilities[4] = mk_special_ability("Deadly Accuracy", "The user deals massive damage by using its long-range weapon.", 0, 1, 63)
special_abilities[5] = mk_special_ability("Flaming Vortex", "The user conjures a flaming vortex that damages and burns the target.", 0, 0, 4)
special_abilities[6] = mk_special_ability("Inferno", "The user creates a powerful inferno to damage the enemy.", 0, 0, 4)
special_abilities[7] = mk_special_ability("Hurricane", "The user conjures a hurricane which lifts up and damages the opponent.", 0, 0, 10)
special_abilities[8] = mk_special_ability("Whirlpool", "The user conjures a whirlpool which damages the enemy.", 0, 0, 2)
special_abilities[9] = mk_special_ability("Landslide", "The user conjures a landslide which damages and traps the enemy.", 0, 0, 16)
special_abilities[10] = mk_special_ability("Extinguish", "If the enemy is of the Fire element, this attack doubles in damage.", 0, 0, 18)
special_abilities[11] = mk_special_ability("Scald", "The user douses the enemy with scalding hot water.", 0, 0, 2)
special_abilities[12] = mk_special_ability("Speedster", "The faster the user is, the higher the damage.", 0, 0, 63)
special_abilities[13] = mk_special_ability("Power Trick", "This special ability uses the enemy's attack stat against them.", 0, 0, 63)
special_abilities[14] = mk_special_ability("Platinum Power Play", "The user deals massive damage by using its close-range weapon.", 0, 2, 63)
special_abilities[15] = mk_special_ability("Guard Stance", "The user guards themselves to avoid any damage.", 0, 0, 16)
special_abilities[16] = mk_special_ability("Honor Amongst Thieves", "If the character and the enemy are of the same element, both characters will restore 10% of their health. However, if they are not of the same element, the character that uses this ability will steal 10% of the enemy's health(damage does not bypass armor).", 0, 0, 63)
special_abilities[17] = mk_special_ability("Good Samaritan", "Heals the status of an enemy, if any.", 0, 0, 63)
special_abilities[18] = mk_special_ability("Call To Arms", "Self-inflicts 'Frenzy' status for a variable amount of turns. The amount of turns depends on the strength of the currently attached weapon.", 0, 0, 63)

-- Define items
function mk_item(n, e, it, ir, ie, c, av)
	return {Name=n, Effect=e, ItemType=it, ItemRank=ir, ItemElement=ie, Cost=c, AvailableAtLevel=av}
end

function mk_item_elemental_exp_spell_1(ie)
	return mk_item("Elemental Exp. Spell Rank 1", "Raises the character's level by one if the character's element matches the item's element, and one-half otherwise.", 0, 1, ie, 0, 30)
end

function mk_item_elemental_exp_spell_2(ie)
	return mk_item("Elemental Exp. Spell Rank 2", "Raises the character's level by two if the character's element matches the item's element, and one otherwise.", 0, 2, ie, 0, 30)
end

function mk_item_elemental_exp_spell_3(ie)
	return mk_item("Elemental Exp. Spell Rank 3", "Raises the character's level by five if the character's element matches the item's element, and two otherwise.", 0, 3, ie, 0, 30)
end

function mk_item_elemental_exp_spell_a(ie)
	return mk_item("Elemental Exp. Spell Rank A", "Raises the character's level by ten if the character's element matches the item's element, and five otherwise.", 0, 4, ie, 0, 30)
end

function mk_item_energy_orb(ie)
	return mk_item("Energy Orb", "Yields 500 experience if the character's element matches the item's element, 250 otherwise.", 0, 0, ie, 5000, 30)
end

function mk_item_tome(n, e, ie, av)
	return mk_item(n, e, 2, 0, ie, 0, av)
end

function mk_item_stone(n, e, ie, av)
	return mk_item(n, e, 2, 0, ie, 0, av)
end

num_items = 45
items = {}
items[0] = mk_item("Exp. Spell Rank 1", "Raises the character's level by one-half.", 0, 1, 0, 100000, 5)
items[1] = mk_item("Exp. Spell Rank 2", "Raises the character's level by one.", 0, 2, 0, 300000, 10)
items[2] = mk_item("Exp. Spell Rank 3", "Raises the character's level by two.", 0, 3, 0, 550000, 20)
items[3] = mk_item("Exp. Spell Rank A", "Raises the character's level by five.", 0, 4, 0, 850000, 40)
items[4] = mk_item_elemental_exp_spell_1(1)
items[5] = mk_item_elemental_exp_spell_2(1)
items[6] = mk_item_elemental_exp_spell_3(1)
items[7] = mk_item_elemental_exp_spell_a(1)
items[8] = mk_item_elemental_exp_spell_1(2)
items[9] = mk_item_elemental_exp_spell_2(2)
items[10] = mk_item_elemental_exp_spell_3(2)
items[11] = mk_item_elemental_exp_spell_a(2)
items[12] = mk_item_elemental_exp_spell_1(3)
items[13] = mk_item_elemental_exp_spell_2(3)
items[14] = mk_item_elemental_exp_spell_3(3)
items[15] = mk_item_elemental_exp_spell_a(3)
items[16] = mk_item_elemental_exp_spell_1(4)
items[17] = mk_item_elemental_exp_spell_2(4)
items[18] = mk_item_elemental_exp_spell_3(4)
items[19] = mk_item_elemental_exp_spell_a(4)
items[20] = mk_item_elemental_exp_spell_1(5)
items[21] = mk_item_elemental_exp_spell_2(5)
items[22] = mk_item_elemental_exp_spell_3(5)
items[23] = mk_item_elemental_exp_spell_a(5)
items[24] = mk_item_energy_orb(1)
items[25] = mk_item_energy_orb(2)
items[26] = mk_item_energy_orb(3)
items[27] = mk_item_energy_orb(4)
items[28] = mk_item_energy_orb(5)
items[29] = mk_item("Steel Plate", "Restores the character's armor.", 1, 0, 0, 3000, 10)
items[30] = mk_item("Curing Spell", "Cures the character of any status.", 1, 0, 0, 5500, 20)
items[31] = mk_item("Healing Spell Rank 1", "Restores 20% of the character's health.", 1, 1, 0, 20000, 0)
items[32] = mk_item("Healing Spell Rank 2", "Restores 40% of the character's health.", 1, 2, 0, 65000, 25)
items[33] = mk_item("Healing Spell Rank 3", "Restores 80% of the character's health.", 1, 3, 0, 85000, 40)
items[34] = mk_item("Healing Spell Rank A", "Heals the character completely and cures the character of any statuses.", 1, 4, 0, 125000, 90)
items[35] = mk_item_tome("Tome of the Earth", "An ancient tome of long-forgotten knowledge. Reading this tome grants the character the powers of the Earth element.", 1, 30)
items[36] = mk_item_tome("Tome of the Sky", "An ancient tome of long-forgotten knowledge. Reading this tome grants the character the powers of the Air element.", 2, 30)
items[37] = mk_item_tome("Tome of Flames", "An ancient tome of long-forgotten knowledge. Reading this tome grants the character the powers of the Fire element.", 3, 30)
items[38] = mk_item_tome("Tome of the Sea", "An ancient tome of long-forgotten knowledge. Reading this tome grants the character the powers of the Water element.", 4, 30)
items[39] = mk_item_tome("Tome of Time", "An ancient tome of long-forgotten knowledge. Reading this tome grants the character the powers of the Mystic element.", 5, 90)
items[40] = mk_item_stone("The Wolf's Stone", "The Founding Stone imbued with the Spirit of the Wolf. It gives off a strange aura...", 1, 30)
items[41] = mk_item_stone("The Eagle's Stone", "The Founding Stone imbued with the Spirit of the Eagle. It gives off a strange aura...", 2, 30)
items[42] = mk_item_stone("The Dragon's Stone", "The Founding Stone imbued with the Spirit of the Dragon. It gives off a strange aura...", 3, 30)
items[43] = mk_item_stone("The Sea Serpent's Stone", "The Founding Stone imbued with the Spirit of the Sea Serpent. It gives off a strange aura...", 4, 30)
items[44] = mk_item_stone("The Spatial Stone", "A mystical stone. The air around the stone appears to be vibrating...", 5, 90)

-- Returns requested character element
function GetElement(n)
	return elements[n]
end

-- Returns requested character rank
function GetRank(n)
	return ranks[n]
end

-- Returns requested status
function GetStatus(n)
	return statuses[n]
end

-- Returns requested weapon
function GetWeapon(n)
	return weapons[n]
end

-- Returns requested passive ability
function GetPassiveAbility(n)
	return passive_abilities[n]
end

-- Returns requested special ability
function GetSpecialAbility(n)
	return special_abilities[n]
end

-- Returns requested item
function GetItem(n)
	return items[n]
end