EverGrandeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_OnLoad
	.byte 0

EverGrandeCity_OnTransition:
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather	
	end

EverGrandeCity_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_EventScript_HideBlue
	call_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_EventScript_ShowBlue
	end

EverGrandeCity_EventScript_HideBlue::
	setflag FLAG_HIDE_BLUE
	return

EverGrandeCity_EventScript_ShowBlue::
	clearflag FLAG_HIDE_BLUE
	return

EverGrandeCity_EventScript_VictoryRoadSign::
	msgbox EverGrandeCity_Text_EnteringVictoryRoad, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_CitySign::
	msgbox EverGrandeCity_Text_CitySign, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_PokemonLeagueSign::
	msgbox EverGrandeCity_Text_EnteringPokemonLeague, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_SetVisitedEverGrande::
	setflag FLAG_VISITED_EVER_GRANDE_CITY
	setvar VAR_TEMP_1, 1
	end

EverGrandeCity_EventScript_BlueBattle::
	lockall
	call_if_unset FLAG_FIRST_TALK_BLUE, EverGrandeCity_EventScript_BlueIntro
	setflag FLAG_FIRST_TALK_BLUE
	call_if_unset FLAG_DEFEATED_METEOR_FALLS_STEVEN, EverGrandeCity_EventScript_YouAreTooWeak
	call_if_set FLAG_DEFEATED_BLUE, EverGrandeCity_EventScript_OtherTrainersInHoenn
	msgbox EverGrandeCity_Text_YouBeatSteven, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLUE, EverGrandeCity_Text_BlueDefeat
	goto EverGrandeCity_EventScript_OtherTrainersInHoenn
	fadedefaultbgm
	releaseall
	end

EverGrandeCity_EventScript_BlueIntro::
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	msgbox EverGrandeCity_Text_BlueIntro, MSGBOX_DEFAULT
	return

EverGrandeCity_EventScript_YouAreTooWeak::
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	msgbox EverGrandeCity_Text_YouAreTooWeak, MSGBOX_DEFAULT
	fadedefaultbgm
	releaseall
	end

EverGrandeCity_EventScript_BlueAfterDefeat::
	playbgm MUS_RG_RIVAL_EXIT, FALSE
	msgbox EverGrandeCity_Text_BlueOutro, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DEFEATED_BLUE
	msgbox EverGrandeCity_Text_OtherTrainersInHoenn, MSGBOX_DEFAULT
	fadedefaultbgm
	goto EverGrandeCity_EventScript_OtherTrainersInHoenn
	end

EverGrandeCity_EventScript_OtherTrainersInHoenn::
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_LEAF, EverGrandeCity_EventScript_RedLeafDefeated
	call_if_set FLAG_DEFEATED_RED, EverGrandeCity_EventScript_RedLeafDefeated
	call_if_unset FLAG_DEFEATED_LEAF, EverGrandeCity_EventScript_LeafHint
	call_if_set FLAG_DEFEATED_LEAF, EverGrandeCity_EventScript_LeafCheck
	setflag FLAG_TALK_BLUE_LEAF
	call_if_unset FLAG_DEFEATED_RED, EverGrandeCity_EventScript_RedHint
	call_if_set FLAG_DEFEATED_RED, EverGrandeCity_EventScript_RedCheck
	setflag FLAG_TALK_BLUE_RED
	goto_if_eq VAR_0x8004, 2, EverGrandeCity_EventScript_YouAreABattleLegend  @ Both defeated
	releaseall
	end

EverGrandeCity_EventScript_RedLeafDefeated::
	addvar VAR_0x8004, 1
	return

EverGrandeCity_EventScript_YouAreABattleLegend::
	msgbox EverGrandeCity_Text_YouAreABattleLegend, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_EventScript_LeafHint::
	msgbox EverGrandeCity_Text_LeafHint, MSGBOX_DEFAULT
	return

EverGrandeCity_EventScript_LeafCheck::
	call_if_unset FLAG_TALK_BLUE_LEAF, EverGrandeCity_EventScript_LeafDefeated
	return

EverGrandeCity_EventScript_LeafDefeated::
	msgbox EverGrandeCity_Text_LeafDefeated, MSGBOX_DEFAULT
	goto EverGrandeCity_EventScript_RedHint
	return

EverGrandeCity_EventScript_RedHint::
	msgbox EverGrandeCity_Text_RedHint, MSGBOX_DEFAULT
	return

EverGrandeCity_EventScript_RedCheck::
	call_if_unset FLAG_TALK_BLUE_RED, EverGrandeCity_EventScript_RedDefeated
	return

EverGrandeCity_EventScript_RedDefeated::
	msgbox EverGrandeCity_Text_RedDefeated, MSGBOX_DEFAULT
	return

EverGrandeCity_Text_EnteringVictoryRoad:
	.string "Entering Victory Road$"

EverGrandeCity_Text_EnteringPokemonLeague:
	.string "Entering Pokémon League\n"
	.string "Center Gate$"

EverGrandeCity_Text_CitySign:
	.string "Ever Grande City\p"
	.string "“The paradise of flowers, the sea,\n"
	.string "and Pokémon.”$"

EverGrandeCity_Text_BlueIntro:
	.string "Who are you?\p"
	.string "… … … … … … …\p"
	.string "Oh, so you're the new Hoenn Champion.\p"
	.string "My name's Blue.\n"
	.string "I was once the Kanto Champion.\p"
	.string "Although it was short-lived thanks\n"
	.string "to Red.$"

EverGrandeCity_Text_YouAreTooWeak:
	.string "What's that, you want to fight me?\p"
	.string "Dream on! Even though you're the\n"
	.string "Champion, you probably got lucky,\l"
	.string "you wouldn't last even a minute\l"
	.string "against me.\p"
	.string "Let's see, if you win against a\n"
	.string "big name of Champion caliber,\l"
	.string "maybe I'll consider battling you.\p"
	.string "But for now, smell ya later!$"

EverGrandeCity_Text_YouBeatSteven:
	.string "Oh so you beat Steven?\p"
	.string "Not bad, you might actually pose\n"
	.string "a challenge after all.\p"
	.string "Alright!\n"
	.string "Come on, I'll take you on!$"

EverGrandeCity_Text_BlueDefeat:
	.string "No way!\n"
	.string "How the heck did I lose?!$"

EverGrandeCity_Text_BlueOutro:
	.string "…Tch, all right, I was wrong.\n"
	.string "You're the real deal.\l"
	.string "You are a good trainer.\p" 
	.string "But I'm going to beat you someday.\n"
	.string "Don't you forget it!\p"

EverGrandeCity_Text_OtherTrainersInHoenn:
	.string "By the way, I didn't come alone\n"
	.string "on that trip.\p"
	.string "Some of my friends came with me\n"
	.string "and we separated after arriving\l"
	.string "in Hoenn.\p"
	.string "You can try to battle them, if you\n"
	.string "can find them, that is!\p"
	.string "Well, since I'm generous, I can\n"
	.string "give you some hints.$"

EverGrandeCity_Text_LeafHint:
	.string "One of my friends likes nature,\n"
	.string "as her name implies, actually.\p"
	.string "You should try to look for places\n"
	.string "with a lot of greenery.$"

EverGrandeCity_Text_LeafDefeated:
	.string "So you found Leaf?\n"
	.string "You even won against her, amazing!\p"
	.string "Yeah my friends are not the\n"
	.string "talkative type, but their battle\l"
	.string "skills are unmatched.\p"
	.string "Well, except by me of course!\p"
	.string "… … … … …\n"
	.string "What about the other, you say?$"

EverGrandeCity_Text_RedHint:
	.string "My other friend is kinda awkward,\n"
	.string "he's the solitary type.\p"
	.string "He wouldn't want to meet anyone,\n"
	.string "so he's probably at a place where\l"
	.string "nobody can find him.\p"
	.string "You know, like a recluse or a\n"
	.string "caveman.$"

EverGrandeCity_Text_RedDefeated:
	.string "Well, aren't you quite something?\n"
	.string "You defeated Red too!?\p"
	.string "That's great!\p"

EverGrandeCity_Text_YouAreABattleLegend:
	.string "You've shown us the power of Hoenn!\p"
	.string "Defeating all three of us, you\n"
	.string "truly are a Battle Legend!$"
