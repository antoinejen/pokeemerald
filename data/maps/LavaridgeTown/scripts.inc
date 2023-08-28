.set LOCALID_RIVAL_ON_BIKE, 7
.set LOCALID_RIVAL, 8

LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	.byte 0

LavaridgeTown_OnTransition:
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_RIVAL, 11, 9
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_RivalTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto LavaridgeTown_EventScript_RivalGiveGoGoggles
	end

LavaridgeTown_EventScript_RivalTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto LavaridgeTown_EventScript_RivalGiveGoGoggles
	end

LavaridgeTown_EventScript_RivalTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto LavaridgeTown_EventScript_RivalGiveGoGoggles
	end

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	call LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_0x8008, 0, LavaridgeTown_EventScript_RivalApproachPlayer0
	call_if_eq VAR_0x8008, 1, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_eq VAR_0x8008, 2, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BattleBrendan
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_BattleMay
	end

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_RivalApproachPlayer0::
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer0
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalApproachPlayer0:
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	step_end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BattleMay::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LavaridgeTown_EventScript_BattleMayTreecko
	case 1, LavaridgeTown_EventScript_BattleMayTorchic
	case 2, LavaridgeTown_EventScript_BattleMayMudkip
	end

LavaridgeTown_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LAVARIDGE_TREECKO, LavaridgeTown_Text_MayDefeat
	goto LavaridgeTown_EventScript_MayGiveGoGoggles
	end

LavaridgeTown_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LAVARIDGE_TORCHIC, LavaridgeTown_Text_MayDefeat
	goto LavaridgeTown_EventScript_MayGiveGoGoggles
	end

LavaridgeTown_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LAVARIDGE_MUDKIP, LavaridgeTown_Text_MayDefeat
	goto LavaridgeTown_EventScript_MayGiveGoGoggles
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BattleBrendan::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LavaridgeTown_EventScript_BattleBrendanTreecko
	case 1, LavaridgeTown_EventScript_BattleBrendanTorchic
	case 2, LavaridgeTown_EventScript_BattleBrendanMudkip
	end

LavaridgeTown_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LAVARIDGE_TREECKO, LavaridgeTown_Text_BrendanDefeat
	goto LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LAVARIDGE_TORCHIC, LavaridgeTown_Text_BrendanDefeat
	goto LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LAVARIDGE_MUDKIP, LavaridgeTown_Text_BrendanDefeat
	goto LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	call_if_eq VAR_0x8008, 0, LavaridgeTown_EventScript_MoveRival0
	call_if_eq VAR_0x8008, 1, LavaridgeTown_EventScript_MoveRival1
	call_if_eq VAR_0x8008, 2, LavaridgeTown_EventScript_MoveRival2
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 0, LavaridgeTown_EventScript_RivalExit0
	call_if_eq VAR_0x8008, 1, LavaridgeTown_EventScript_RivalExit1
	call_if_eq VAR_0x8008, 2, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_MoveRival0::
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 9, 16
	return

LavaridgeTown_EventScript_MoveRival1::
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 10, 16
	return

LavaridgeTown_EventScript_MoveRival2::
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 11, 16
	return

LavaridgeTown_EventScript_RivalExit0::
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit0
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit0:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_RivalExit2:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_TOGEPI
	release
	end

LavaridgeTown_EventScript_ReceivedEgg::
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
	.string "May: {PLAYER}{KUN}! Long time no see!\p"
	.string "Oh? While I visited the Herb Shop,\n"
	.string "you were getting ready to challenge\l"
	.string "the Lavaridge Gym.\p"
	.string "You must have collected\n"
	.string "good Pokémon…\l"
	.string "No, I believe you raised some.\p"
	.string "Do you mind if I prove that theory?$"

LavaridgeTown_Text_MayDefeat:
	.string "I was right after all!\p"
	.string "I guess it would be okay for you to\n"
	.string "have this.$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
	.string "May: With those Go-Goggles, you'll\n"
	.string "have no trouble getting through the\l"
	.string "desert near Route 111.\p"
	.string "But, wow, {PLAYER}{KUN}…\n"
	.string "Challenging Gyms…\p"
	.string "You're trying hard because you don't\n"
	.string "want to lose to me, I bet!\p"
	.string "{PLAYER}{KUN}, I think I should challenge\n"
	.string "your dad in Petalburg Gym after\l"
	.string "this one.\p"
	.string "See you again!$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
	.string "Brendan: {PLAYER}, hey, it's been a while.\n"
	.string "How's it going?\p"
	.string "Hmm…\n"
	.string "That's a decent collection of Badges.\p"
	.string "But I want to see how those badges you\n"
	.string "got translate into actual battle skills!"

LavaridgeTown_Text_BrendanDefeat:
	.string "As expected from you.\p"
	.string "All right, then.\n"
	.string "You may as well have this.$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
	.string "Brendan: Keep those with you if you're\n"
	.string "planning on going into that desert near\l"
	.string "Route 111.\p"
	.string "There should be some Pokémon that\n"
	.string "are exclusively desert-dwellers.\l"
	.string "You might look around for those.\p"
	.string "As for me…\n"
	.string "I'm considering challenging Norman,\l"
	.string "the Gym Leader of Petalburg afterwards.\p"
	.string "Unlike you, {PLAYER}, your dad looks\n"
	.string "like he really is tough.\p"
	.string "See you around!$"

LavaridgeTown_Text_HaveEggWillYouTakeIt:
	.string "I have here an Egg.\p"
	.string "I'd hoped to hatch it by covering it in\n"
	.string "hot sand by the hot springs.\l"
	.string "But that doesn't seem to be enough…\p"
	.string "I've heard it would be best if it were\n"
	.string "kept together with Pokémon and\l"
	.string "carried about.\p"
	.string "You are a Trainer, yes?\n"
	.string "And your Pokémon radiate vitality.\p"
	.string "So, what say you?\n"
	.string "Will you take this Egg to hatch?$"

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg:
	.string "Good! I hope you'll walk plenty with\n"
	.string "this here Egg!$"

LavaridgeTown_Text_ReceivedTheEgg:
	.string "{PLAYER} received the Egg.$"

LavaridgeTown_Text_NoRoomForThisEgg:
	.string "Oh? You've too many Pokémon.\n"
	.string "There's no room for this Egg…$"

LavaridgeTown_Text_AsYouWishThen:
	.string "As you wish, then…\p"
	.string "If you have a change of heart about\n"
	.string "hatching this Egg, I will be here.$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
	.string "Every so often, an Egg will be found at\n"
	.string "the Pokémon Day Care.\p"
	.string "Or at least that's how the rumor goes.$"

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "We draw as much hot water as we need,\n"
	.string "and yet the hot springs never run dry.\p"
	.string "Isn't it magical?\p"
	.string "These hot springs appear near active\n"
	.string "volcanoes. Veins of water under the\l"
	.string "ground are heated by magma to well up\l"
	.string "as hot springs.$"

LavaridgeTown_Text_PokemonNippedBackside:
	.string "Being buried in this hot sand is…\n"
	.string "Sigh…\p"
	.string "So warm and heavenly…\p"
	.string "Eh? Gyaah! Ouch!\p"
	.string "A Pokémon nipped my backside!$"

LavaridgeTown_Text_OhYouLikeHotSprings:
	.string "Oh, you like hot springs, do you?\p"
	.string "That's surprising for one as young\n"
	.string "as you.$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
	.string "I bathe in the hot springs every day.\p"
	.string "I want to become a beautiful and strong\n"
	.string "Gym Leader like Flannery.$"

LavaridgeTown_Text_IfPokemonInHotSprings:
	.string "If people put Pokémon in hot springs,\n"
	.string "it might be seriously strange.\p"
	.string "Why, it might be an electric bath, or\n"
	.string "a bubble bath, or even a lava bath…$"

LavaridgeTown_Text_HotSpringsClaims:
	.string "They're claiming that these hot springs\n"
	.string "are good for calming nervous tension,\l"
	.string "relieving aching muscles, solving\l"
	.string "romantic problems, and attracting\l"
	.string "money…$"

LavaridgeTown_Text_TownSign:
	.string "Lavaridge Town\p"
	.string "“Pokémon Center Hot Springs\n"
	.string "An excellent place for relaxing!”$"

LavaridgeTown_Text_GymSign:
	.string "Lavaridge Town Pokémon Gym\n"
	.string "Leader: Flannery\l"
	.string "“One with a fiery passion that burns!”$"

LavaridgeTown_Text_HerbShopSign:
	.string "Pokémon Herb Shop\n"
	.string "“Bitter taste--better cure!”$"

