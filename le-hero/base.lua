--[[
base.lua
Copyright (c) 2020 Daniel Buckley
--]]

-- Define character elements
elements = {}
elements[0] = {Name="Basic", ArmorPercent=15, ArmorTurns=50, BaseAttack=13, BaseSpeed=13, BaseHealth=28}
elements[1] = {Name="Earth", ArmorPercent=35, ArmorTurns=60, BaseAttack=22, BaseSpeed=14, BaseHealth=70}
elements[2] = {Name="Air", ArmorPercent=30, ArmorTurns=60, BaseAttack=17, BaseSpeed=22, BaseHealth=49}
elements[3] = {Name="Fire", ArmorPercent=30, ArmorTurns=60, BaseAttack=17, BaseSpeed=17, BaseHealth=62}
elements[4] = {Name="Water", ArmorPercent=35, ArmorTurns=60, BaseAttack=14, BaseSpeed=20, BaseHealth=56}
elements[5] = {Name="Mystic", ArmorPercent=50, ArmorTurns=150, BaseAttack=26, BaseSpeed=26, BaseHealth=78}
elements[6] = {Name="Alpha", ArmorPercent=40, ArmorTurns=25, BaseAttack=29, BaseSpeed=29, BaseHealth=84}

-- Define character ranks
ranks = {}
ranks[0] = {Name="F", AttackBoost=0, SpeedBoost=0, HealthBoost=0}
ranks[1] = {Name="E", AttackBoost=3, SpeedBoost=3, HealthBoost=4}
ranks[2] = {Name="D", AttackBoost=8, SpeedBoost=8, HealthBoost=10}
ranks[3] = {Name="C", AttackBoost=15, SpeedBoost=15, HealthBoost=15}
ranks[4] = {Name="B", AttackBoost=30, SpeedBoost=30, HealthBoost=25}
ranks[5] = {Name="A", AttackBoost=45, SpeedBoost=45, HealthBoost=40}
ranks[6] = {Name="Z", AttackBoost=60, SpeedBoost=60, HealthBoost=50}

-- Define character statuses
num_statuses = 14
statuses = {}
statuses[0] = {Name="Burn", Effect="Damages character 1% of their maximum health every turn for 15 turns.", EffectLength=15, StatusType=0}
statuses[1] = {Name="Poison", Effect="Damages character 3% of their maximum health every turn for 15 turns.", EffectLength=15, StatusType=0}
statuses[2] = {Name="Enlightened", Effect="The character becomes enlightened, and can heal itself for 5 turns.", EffectLength=5, StatusType=0}
statuses[3] = {Name="Guarding", Effect="The character is protected from any damage for 3 turns.", EffectLength=3, StatusType=0}
statuses[4] = {Name="Mystified", Effect="The character becomes mystified by its enemy and cannot attack.", EffectLength=5, StatusType=1}
statuses[5] = {Name="Enraged", Effect="The character becomes enraged and is forced to attack only with its weapon.", EffectLength=5, StatusType=1}
statuses[6] = {Name="Weightless", Effect="The user becomes weightless and floats up, making it impossible to use close-range weapons.", EffectLength=1, StatusType=1}
statuses[7] = {Name="Claustrophobic", Effect="The character is trapped in a tight space, making it impossible to use long-range weapons.", EffectLength=1, StatusType=1}
statuses[8] = {Name="Frozen", Effect="The character is trapped in ice and is forced to pass its turn.", EffectLength=5, StatusType=1}
statuses[9] = {Name="Amnesiac", Effect="The character has temporary amnesia, and cannot remember how to use its special ability.", EffectLength=1, StatusType=1}
statuses[10] = {Name="Shattered Armor", Effect="Removes the effect of armor from the character.", EffectLength=1, StatusType=2}
statuses[11] = {Name="Unworthy", Effect="This character is deemed unworthy by its enemy. It is damaged by 50% of its maximum health, removed of armor, and forced to pass its turn.", EffectLength=1, StatusType=3}
statuses[12] = {Name="Protecting", Effect="The character is protected from any damage for 1 turn.", EffectLength=1, StatusType=3}
statuses[13] = {Name="Killing Spree", Effect="Raises the characters attack and speed by 80% and heals for 40% of damage dealt with a weapon in the previous turn.", EffectLength=0, StatusType=3}

-- Define weapons
num_weapons = 56
weapons = {}
-- Basic Weapons
weapons[0] = {CollectionIndex=0, Category=1, Handling=1, Weight=0, Range=1, DamageType=0, Name="Slingshot", Element=0, Strength=10, CanInflictStatus=false}
weapons[1] = {CollectionIndex=1, Category=2, Handling=0, Weight=1, Range=0, DamageType=0, Name="Sword", Element=0, Strength=23, CanInflictStatus=false}
weapons[2] = {CollectionIndex=2, Category=3, Handling=1, Weight=0, Range=2, DamageType=0, Name="Bow", Element=0, Strength=18, CanInflictStatus=false}
weapons[3] = {CollectionIndex=3, Category=2, Handling=0, Weight=0, Range=0, DamageType=0, Name="Dagger", Element=0, Strength=15, CanInflictStatus=false}
weapons[4] = {CollectionIndex=4, Category=2, Handling=1, Weight=2, Range=0, DamageType=0, Name="Katana", Element=0, Strength=25, CanInflictStatus=false}
weapons[5] = {CollectionIndex=5, Category=4, Handling=1, Weight=0, Range=1, DamageType=0, Name="Javelin", Element=0, Strength=27, CanInflictStatus=false}
weapons[6] = {CollectionIndex=6, Category=2, Handling=1, Weight=1, Range=0, DamageType=1, Name="Cursed Blade", Element=0, Strength=35, CanInflictStatus=false}
weapons[7] = {CollectionIndex=7, Category=7, Handling=1, Weight=0, Range=1, DamageType=1, Name="Beginner's Elemental Staff", Element=0, Strength=37, CanInflictStatus=true, InflictedStatus=4}

-- Earth Weapons
weapons[8] = {CollectionIndex=0, Category=2, Handling=0, Weight=1, Range=0, DamageType=0, Name="Dull Wolf Katana", Element=1, Strength=45, CanInflictStatus=false}
weapons[9] = {CollectionIndex=1, Category=4, Handling=1, Weight=1, Range=1, DamageType=0, Name="Ancient Spear", Element=1, Strength=49, CanInflictStatus=true, InflictedStatus=1}
weapons[10] = {CollectionIndex=2, Category=5, Handling=0, Weight=1, Range=0, DamageType=0, Name="Bone Club", Element=1, Strength=54, CanInflictStatus=false}
weapons[11] = {CollectionIndex=3, Category=3, Handling=1, Weight=0, Range=1, DamageType=0, Name="Marksman's Crossbow", Element=1, Strength=60, CanInflictStatus=false}
weapons[12] = {CollectionIndex=4, Category=2, Handling=1, Weight=1, Range=0, DamageType=0, Name="Earthen Scythe", Element=1, Strength=67, CanInflictStatus=true, InflictedStatus=7}
weapons[13] = {CollectionIndex=5, Category=2, Handling=1, Weight=2, Range=0, DamageType=0, Name="Tungsten Katana", Element=1, Strength=71, CanInflictStatus=false}
weapons[14] = {CollectionIndex=6, Category=7, Handling=1, Weight=0, Range=1, DamageType=1, Name="Staff of the Wolf's Eye", Element=1, Strength=75, CanInflictStatus=false}
weapons[15] = {CollectionIndex=7, Category=2, Handling=1, Weight=2, Range=0, DamageType=0, Name="Wolf's Eye Katana", Element=1, Strength=80, CanInflictStatus=true, InflictedStatus=4}

-- Air Weapons
weapons[16] = {CollectionIndex=0, Category=3, Handling=0, Weight=0, Range=0, DamageType=0, Name="Tattered Eagle Bow", Element=2, Strength=45, CanInflictStatus=true, InflictedStatus=6}
weapons[17] = {CollectionIndex=1, Category=2, Handling=0, Weight=0, Range=0, DamageType=0, Name="Sky Blade", Element=2, Strength=51, CanInflictStatus=false}
weapons[18] = {CollectionIndex=2, Category=1, Handling=1, Weight=0, Range=1, DamageType=0, Name="Reinforced Slingshot", Element=2, Strength=56, CanInflictStatus=false}
weapons[19] = {CollectionIndex=3, Category=3, Handling=1, Weight=1, Range=2, DamageType=1, Name="Poisoned Bow", Element=2, Strength=60, CanInflictStatus=true, InflictedStatus=1}
weapons[20] = {CollectionIndex=4, Category=2, Handling=0, Weight=0, Range=0, DamageType=0, Name="Lightening Sword", Element=2, Strength=64, CanInflictStatus=true, InflictedStatus=6}
weapons[21] = {CollectionIndex=5, Category=4, Handling=1, Weight=1, Range=1, DamageType=1, Name="Spear of Shattering", Element=2, Strength=69, CanInflictStatus=true, InflictedStatus=10}
weapons[22] = {CollectionIndex=6, Category=7, Handling=1, Weight=0, Range=1, DamageType=1, Name="Staff of the Eagle's Talon", Element=2, Strength=75, CanInflictStatus=false}
weapons[23] = {CollectionIndex=7, Category=3, Handling=1, Weight=2, Range=2, DamageType=0, Name="Spirit Eagle Bow", Element=2, Strength=80, CanInflictStatus=true, InflictedStatus=4}

-- Fire Weapons
weapons[24] = {CollectionIndex=0, Category=2, Handling=0, Weight=0, Range=0, DamageType=0, Name="Dull Dragon Sword", Element=3, Strength=45, CanInflictStatus=true, InflictedStatus=0}
weapons[25] = {CollectionIndex=1, Category=3, Handling=1, Weight=0, Range=2, DamageType=0, Name="Flaming Bow", Element=3, Strength=53, CanInflictStatus=true, InflictedStatus=0}
weapons[26] = {CollectionIndex=2, Category=2, Handling=0, Weight=0, Range=0, DamageType=0, Name="Scorching Dagger", Element=3, Strength=49, CanInflictStatus=true, InflictedStatus=0}
weapons[27] = {CollectionIndex=3, Category=2, Handling=0, Weight=1, Range=0, DamageType=0, Name="Volcanic Sword", Element=3, Strength=57, CanInflictStatus=true, InflictedStatus=0}
weapons[28] = {CollectionIndex=4, Category=2, Handling=0, Weight=2, Range=0, DamageType=0, Name="Infernal Axe", Element=3, Strength=68, CanInflictStatus=false}
weapons[29] = {CollectionIndex=5, Category=6, Handling=1, Weight=2, Range=0, DamageType=0, Name="Lava Hammer", Element=3, Strength=72, CanInflictStatus=false}
weapons[30] = {CollectionIndex=6, Category=7, Handling=1, Weight=0, Range=1, DamageType=1, Name="Staff of the Dragon's Horn", Element=3, Strength=75, CanInflictStatus=false}
weapons[31] = {CollectionIndex=7, Category=2, Handling=1, Weight=1, Range=0, DamageType=0, Name="Dragon Claw Sword", Element=3, Strength=80, CanInflictStatus=true, InflictedStatus=4}

-- Water Weapons
weapons[32] = {CollectionIndex=0, Category=3, Handling=1, Weight=0, Range=2, DamageType=0, Name="Tattered Serpent Bow", Element=4, Strength=45, CanInflictStatus=false}
weapons[33] = {CollectionIndex=1, Category=2, Handling=1, Weight=1, Range=0, DamageType=0, Name="Ice Scimitar", Element=4, Strength=50, CanInflictStatus=false}
weapons[34] = {CollectionIndex=2, Category=3, Handling=1, Weight=0, Range=2, DamageType=0, Name="Frozen Bow", Element=4, Strength=53, CanInflictStatus=true, InflictedStatus=8}
weapons[35] = {CollectionIndex=3, Category=4, Handling=1, Weight=0, Range=0, DamageType=0, Name="Icicle Spear", Element=4, Strength=61, CanInflictStatus=false}
weapons[36] = {CollectionIndex=4, Category=2, Handling=0, Weight=0, Range=0, DamageType=0, Name="Coral Bayonet", Element=4, Strength=66, CanInflictStatus=false}
weapons[37] = {CollectionIndex=5, Category=5, Handling=0, Weight=2, Range=0, DamageType=1, Name="Subzero Mace", Element=4, Strength=71, CanInflictStatus=true, InflictedStatus=8}
weapons[38] = {CollectionIndex=6, Category=7, Handling=1, Weight=0, Range=1, DamageType=1, Name="Staff of the Serpent's Fang", Element=4, Strength=75, CanInflictStatus=false}
weapons[39] = {CollectionIndex=7, Category=3, Handling=1, Weight=0, Range=2, DamageType=0, Name="Sea Serpent Bow", Element=4, Strength=80, CanInflictStatus=true, InflictedStatus=4}

-- Mystic Weapons
weapons[40] = {CollectionIndex=0, Category=0, Handling=0, Weight=0, Range=0, DamageType=0, Name="", Element=5, Strength=45, CanInflictStatus=false}
weapons[41] = {CollectionIndex=1, Category=0, Handling=0, Weight=0, Range=0, DamageType=0, Name="", Element=5, Strength=50, CanInflictStatus=false}
weapons[42] = {CollectionIndex=2, Category=0, Handling=0, Weight=0, Range=0, DamageType=0, Name="", Element=5, Strength=55, CanInflictStatus=false}
weapons[43] = {CollectionIndex=3, Category=0, Handling=0, Weight=0, Range=0, DamageType=0, Name="", Element=5, Strength=60, CanInflictStatus=false}
weapons[44] = {CollectionIndex=4, Category=0, Handling=0, Weight=0, Range=0, DamageType=0, Name="", Element=5, Strength=65, CanInflictStatus=false}
weapons[45] = {CollectionIndex=5, Category=0, Handling=0, Weight=0, Range=0, DamageType=0, Name="", Element=5, Strength=70, CanInflictStatus=false}
weapons[46] = {CollectionIndex=6, Category=7, Handling=0, Weight=0, Range=0, DamageType=0, Name="Elemental Staff", Element=5, Strength=75, CanInflictStatus=false}
weapons[47] = {CollectionIndex=7, Category=0, Handling=0, Weight=0, Range=0, DamageType=0, Name="", Element=5, Strength=80, CanInflictStatus=true, InflictedStatus=4}

-- Alpha Weapons
weapons[48] = {CollectionIndex=0, Category=7, Handling=1, Weight=0, Range=1, DamageType=1, Name="Staff of Simplicity", Element=6, Strength=85, CanInflictStatus=false}
weapons[49] = {CollectionIndex=1, Category=7, Handling=1, Weight=1, Range=1, DamageType=1, Name="Staff of Sky", Element=6, Strength=90, CanInflictStatus=true, InflictedStatus=6}
weapons[50] = {CollectionIndex=2, Category=7, Handling=1, Weight=1, Range=1, DamageType=1, Name="Staff of Land", Element=6, Strength=90, CanInflictStatus=true, InflictedStatus=7}
weapons[51] = {CollectionIndex=3, Category=7, Handling=1, Weight=1, Range=1, DamageType=1, Name="Staff of Flame", Element=6, Strength=90, CanInflictStatus=true, InflictedStatus=0}
weapons[52] = {CollectionIndex=4, Category=7, Handling=1, Weight=1, Range=1, DamageType=1, Name="Staff of Sea", Element=6, Strength=90, CanInflictStatus=false}
weapons[53] = {CollectionIndex=5, Category=7, Handling=1, Weight=1, Range=1, DamageType=1, Name="Staff of Mastery", Element=6, Strength=90, CanInflictStatus=false}
weapons[54] = {CollectionIndex=6, Category=7, Handling=1, Weight=1, Range=1, DamageType=1, Name="Staff of Rage", Element=6, Strength=95, CanInflictStatus=true, InflictedStatus=5}
weapons[55] = {CollectionIndex=7, Category=7, Handling=1, Weight=2, Range=1, DamageType=1, Name="Staff of Creation", Element=6, Strength=100, CanInflictStatus=true, InflictedStatus=11}

-- Define character passive abilities
passive_abilities = {}
passive_abilities[0] = {Name="Passive - Basic", Effect="When Health drops below 50%, the Attack stat is doubled.", NativeElement=0}
passive_abilities[1] = {Name="Passive - Earth", Effect="Power of close-range attacks increase by 30% when battling in Earth terrain.", NativeElement=1}
passive_abilities[2] = {Name="Passive - Air", Effect="Power of long-range attacks increase by 30% when battling in Air terrain.", NativeElement=2}
passive_abilities[3] = {Name="Passive - Fire", Effect="Attack is increased by 10% when battling in Fire terrain.", NativeElement=3}
passive_abilities[4] = {Name="Passive - Water", Effect="Speed is increased by 10% when battling in Water terrain.", NativeElement=4}
passive_abilities[5] = {Name="Passive - Mystic", Effect="", NativeElement=5}
passive_abilities[6] = {Name="Passive - Alpha", Effect="When passing a turn, the Character recovers 25% of it's maximum health.", NativeElement=6}

-- Define character special abilties
num_special_abilities = 19
special_abilities = {}
special_abilities[0] = {Name="Protect", Effect="Protects character from any damage.", CostToLearn=0, WeaponReqs=0, ElementSupport=63}
special_abilities[1] = {Name="Recovery", Effect="Recover 25% of maximum health.", CostToLearn=0, WeaponReqs=0, ElementSupport=63}
special_abilities[2] = {Name="Tricky Mirror", Effect="Transfers the current inflicted status (if one) to the enemy.", CostToLearn=0, WeaponReqs=0, ElementSupport=63}
special_abilities[3] = {Name="Revenge", Effect="The lower the user's current health is, the greater the damage.", CostToLearn=0, WeaponReqs=0, ElementSupport=63}
special_abilities[4] = {Name="Deadly Accuracy", Effect="The user deals massive damage by using its long-range weapon.", CostToLearn=0, WeaponReqs=1, ElementSupport=63}
special_abilities[5] = {Name="Flaming Vortex", Effect="The user conjures a flaming vortex that damages and burns the target.", CostToLearn=0, WeaponReqs=0, ElementSupport=4}
special_abilities[6] = {Name="Inferno", Effect="The user creates a powerful inferno to damage the enemy.", CostToLearn=0, WeaponReqs=0, ElementSupport=4}
special_abilities[7] = {Name="Hurricane", Effect="The user conjures a hurricane which lifts up and damages the opponent.", CostToLearn=0, WeaponReqs=0, ElementSupport=10}
special_abilities[8] = {Name="Whirlpool", Effect="The user conjures a whirlpool which damages the enemy.", CostToLearn=0, WeaponReqs=0, ElementSupport=2}
special_abilities[9] = {Name="Landslide", Effect="The user conjures a landslide which damages and traps the enemy.", CostToLearn=0, WeaponReqs=0, ElementSupport=16}
special_abilities[10] = {Name="Extinguish", Effect="If the enemy is of the Fire element, this attack doubles in damage.", CostToLearn=0, WeaponReqs=0, ElementSupport=18}
special_abilities[11] = {Name="Scald", Effect="The user douses the enemy with scalding hot water.", CostToLearn=0, WeaponReqs=0, ElementSupport=2}
special_abilities[12] = {Name="Speedster", Effect="The faster the user is, the higher the damage.", CostToLearn=0, WeaponReqs=0, ElementSupport=63}
special_abilities[13] = {Name="Power Trick", Effect="This special ability uses the enemy's attack stat against them.", CostToLearn=0, WeaponReqs=0, ElementSupport=63}
special_abilities[14] = {Name="Platinum Power Play", Effect="The user deals massive damage by using its close-range weapon.", CostToLearn=0, WeaponReqs=2, ElementSupport=63}
special_abilities[15] = {Name="Guard Stance", Effect="The user guards themselves to avoid any damage.", CostToLearn=0, WeaponReqs=0, ElementSupport=16}
special_abilities[16] = {Name="Honor Amongst Thieves", Effect="If the character and the enemy are of the same element, both characters will restore 10% of their health. However, if they are not of the same element, the character that uses this ability will steal 10% of the enemy's health(damage does not bypass armor).", CostToLearn=0, WeaponReqs=0, ElementSupport=63}
special_abilities[17] = {Name="Good Samaritan", Effect="Heals the status of an enemy, if any.", CostToLearn=0, WeaponReqs=0, ElementSupport=63}
special_abilities[18] = {Name="Call To Arms", Effect="Self-inflicts 'Killing Spree' status for a variable amount of turns. The amount of turns depends on the strength of the currently attached weapon.", CostToLearn=0, WeaponReqs=0, ElementSupport=63}

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