GraniteCave_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GraniteCave_B2F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, GraniteCave_B2F_OnTransition
	.byte 0

GraniteCave_B2F_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, GraniteCave_B2F_EventScript_EncounterMewtwo
	end

GraniteCave_B2F_OnTransition:
	call_if_unset FLAG_DEFEATED_MEWTWO, GraniteCave_B2F_EventScript_ShowMewtwo
	end

GraniteCave_B2F_EventScript_ShowMewtwo::
	clearflag FLAG_HIDE_MEWTWO
	return

GraniteCave_B2F_EventScript_EncounterMewtwo::
	lock
	faceplayer
	message gText_Gyaoo
	setwildbattle SPECIES_MEWTWO, 70, ITEM_BERSERK_GENE
	waitse
	playmoncry SPECIES_MEWTWO, CRY_MODE_ENCOUNTER
	delay 40
	waitmessage
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	waitbuttonpress
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, GraniteCave_B2F_EventScript_DefeatedMewtwo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GraniteCave_B2F_EventScript_RanFromMewtwo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GraniteCave_B2F_EventScript_RanFromMewtwo
	setflag FLAG_DEFEATED_MEWTWO
	release
	end

GraniteCave_B2F_EventScript_DefeatedMewtwo::
	setflag FLAG_DEFEATED_MEWTWO
	goto Common_EventScript_RemoveStaticPokemon
	end

GraniteCave_B2F_EventScript_RanFromMewtwo::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, SPECIES_MEWTWO
	msgbox GraniteCave_B2F_Text_MewtwoTeleportedAway, MSGBOX_DEFAULT
	release
	end

GraniteCave_B2F_Text_MewtwoTeleportedAway:
	.string "{STR_VAR_1} teleported away.$"
