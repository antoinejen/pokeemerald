.set LOCALID_WALLY, 19

Route118_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route118_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route118_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route118_OnFrame
	.byte 0

Route118_OnTransition:
	call GabbyAndTy_EventScript_UpdateLocation
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_EAST, AbnormalWeather_StartGroudonWeather
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_WEST, AbnormalWeather_StartGroudonWeather
	end

Route118_OnLoad:
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_EAST, AbnormalWeather_EventScript_PlaceTilesRoute118East
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_118_WEST, AbnormalWeather_EventScript_PlaceTilesRoute118West
	end

Route118_OnFrame:
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route118_EventScript_GoodRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_GOOD_ROD, Route118_EventScript_ReceivedGoodRod
	msgbox Route118_Text_YouAgreeGoodRodIsGood, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route118_EventScript_ReceiveGoodRod
	goto_if_eq VAR_RESULT, NO, Route118_EventScript_DeclineGoodRod
	end

Route118_EventScript_ReceiveGoodRod::
	msgbox Route118_Text_IdenticalMindsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_GOOD_ROD
	msgbox Route118_Text_TryYourLuckFishing, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_DeclineGoodRod::
	msgbox Route118_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_ReceivedGoodRod::
	msgbox Route118_Text_TryCatchingMonWithGoodRod, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_Girl::
	msgbox Route118_Text_CanCrossRiversWithSurf, MSGBOX_NPC
	end

Route118_EventScript_RouteSignMauville::
	msgbox Route118_Text_RouteSignMauville, MSGBOX_SIGN
	end

Route118_EventScript_RouteSign119::
	msgbox Route118_Text_RouteSign119, MSGBOX_SIGN
	end

Route118_EventScript_WallyTrigger0::
	lockall
	setvar VAR_0x8008, 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_WALLY, Route118_Movement_WallyApproachLedge0
	waitmovement 0
	goto Route118_EventScript_WallyTrigger
	end

Route118_EventScript_WallyTrigger1::
	lockall
	setvar VAR_0x8008, 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	goto Route118_EventScript_WallyTrigger
	end

Route118_EventScript_WallyTrigger2::
	lockall
	setvar VAR_0x8008, 2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_WALLY, Route118_Movement_WallyApproachLedge2
	waitmovement 0
	goto Route118_EventScript_WallyTrigger
	end

Route118_EventScript_WallyTrigger::
	playse SE_LEDGE
	applymovement LOCALID_WALLY, Route118_Movement_WallyJumpLedge
	waitmovement 0
	delay 30
	msgbox Route118_Text_WallyQuestions, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_WALLY_ROUTE_118, Route118_Text_WallyDefeated
	goto Route118_EventScript_AfterWallyBattle
	end

Route118_EventScript_AfterWallyBattle::
	msgbox Route118_Text_WallyGo, MSGBOX_DEFAULT
	goto Route118_EventScript_WallyExit
	end

Route118_EventScript_WallyExit::
	closemessage
	call_if_eq VAR_0x8008, 0, Route118_EventScript_WallyExit0
	call_if_eq VAR_0x8008, 1, Route118_EventScript_WallyExit1
	call_if_eq VAR_0x8008, 2, Route118_EventScript_WallyExit2
	setvar VAR_ROUTE118_STATE, 1
	removeobject LOCALID_WALLY
	releaseall
	end

Route118_EventScript_WallyExit0::
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchWallyExit
	applymovement LOCALID_WALLY, Route118_Movement_WallyExit0
	waitmovement 0
	return

Route118_EventScript_WallyExit1::
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchWallyExit
	applymovement LOCALID_WALLY, Route118_Movement_WallyExit1
	waitmovement 0
	return

Route118_EventScript_WallyExit2::
	applymovement OBJ_EVENT_ID_PLAYER, Route118_Movement_PlayerWatchWallyExit
	applymovement LOCALID_WALLY, Route118_Movement_WallyExit2
	waitmovement 0
	return

Route118_Movement_PlayerWatchWallyExit:
	delay_16
	walk_in_place_faster_right
	step_end

Route118_Movement_WallyApproachLedge0:
	walk_left
	step_end

Route118_Movement_WallyApproachLedge2:
	walk_right
	step_end

Route118_Movement_WallyJumpLedge:
	jump_2_down
	delay_16
	walk_down
	step_end

Route118_Movement_WallyExit0:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_Movement_WallyExit1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_Movement_WallyExit2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route118_EventScript_Rose::
	trainerbattle_single TRAINER_ROSE_1, Route118_Text_RoseIntro, Route118_Text_RoseDefeat, Route118_EventScript_RegisterRose
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route118_EventScript_RematchRose
	msgbox Route118_Text_RosePostBattle, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_RegisterRose::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route118_Text_RoseRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ROSE_1
	release
	end

Route118_EventScript_RematchRose::
	trainerbattle_rematch TRAINER_ROSE_1, Route118_Text_RoseRematchIntro, Route118_Text_RoseRematchDefeat
	msgbox Route118_Text_RosePostRematch, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Barny::
	trainerbattle_single TRAINER_BARNY, Route118_Text_BarnyIntro, Route118_Text_BarnyDefeat
	msgbox Route118_Text_BarnyPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Wade::
	trainerbattle_single TRAINER_WADE, Route118_Text_WadeIntro, Route118_Text_WadeDefeat
	msgbox Route118_Text_WadePostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Dalton::
	trainerbattle_single TRAINER_DALTON_1, Route118_Text_DaltonIntro, Route118_Text_DaltonDefeat, Route118_EventScript_RegisterDalton
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route118_EventScript_RematchDalton
	msgbox Route118_Text_DaltonPostBattle, MSGBOX_DEFAULT
	release
	end

Route118_EventScript_RegisterDalton::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route118_Text_DaltonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DALTON_1
	release
	end

Route118_EventScript_RematchDalton::
	trainerbattle_rematch TRAINER_DALTON_1, Route118_Text_DaltonRematchIntro, Route118_Text_DaltonRematchDefeat
	msgbox Route118_Text_DaltonPostRematch, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Perry::
	trainerbattle_single TRAINER_PERRY, Route118_Text_PerryIntro, Route118_Text_PerryDefeat
	msgbox Route118_Text_PerryPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Chester::
	trainerbattle_single TRAINER_CHESTER, Route118_Text_ChesterIntro, Route118_Text_ChesterDefeat
	msgbox Route118_Text_ChesterPostBattle, MSGBOX_AUTOCLOSE
	end

Route118_EventScript_Deandre::
	trainerbattle_single TRAINER_DEANDRE, Route118_Text_DeandreIntro, Route118_Text_DeandreDefeat
	msgbox Route118_Text_DeandrePostBattle, MSGBOX_AUTOCLOSE
	end

Route118_Text_WallyQuestions:
	.string "Wally: Hi, {PLAYER}{KUN}!\p"
	.string "It's me, Wally!\n"
	.string "I bet you didn't expect me here!\p"
	.string "Thanks to you, I can explore the\n"
	.string "entire region.\p"
	.string "I met many, many kinds of Pokémon\n"
	.string "during my journey.\p"
	.string "I also trained really, really hard\n"
	.string "with Ralts and the friends I made\l"
	.string "along the way.\p"
	.string "I have matured as a person, and as\n"
	.string "a Trainer.\p"
	.string "And now, I wish to prove myself\n"
	.string "to you once again.\p"
	.string "{PLAYER}{KUN}! I demand a rematch!$"

Route118_Text_WallyDefeated:
	.string "Wow {PLAYER}{KUN}, you're so strong!$"

Route118_Text_WallyGo:
	.string "{PLAYER}{KUN}, you became so much stronger!\p"
	.string "I feel like the gap between us\n"
	.string "has never shrunk...\p"
	.string "But you'll see! I'll come back stronger\n"
	.string "than ever! And when I do, I hope\l"
	.string "you'll be surprised.\p"
	.string "Until then, I'll get even stronger\n"
	.string "so watch your back!$"

Route118_Text_YouAgreeGoodRodIsGood:
	.string "Hmm!\n"
	.string "A Good Rod is really good!\p"
	.string "Wouldn't you agree?$"

Route118_Text_IdenticalMindsTakeThis:
	.string "Hmm!\n"
	.string "We're of identical minds!\p"
	.string "Hmm!\n"
	.string "Take this Good Rod!$"

Route118_Text_TryYourLuckFishing:
	.string "Wherever there's water, try your luck\n"
	.string "at fishing.$"

Route118_Text_DontYouLikeToFish:
	.string "Don't you like to fish?$"

Route118_Text_TryCatchingMonWithGoodRod:
	.string "Try catching all sorts of Pokémon\n"
	.string "with your Good Rod.$"

Route118_Text_CanCrossRiversWithSurf:
	.string "Even if there isn't a boat, you can\n"
	.string "cross rivers and the sea if you have\l"
	.string "a Pokémon that knows Surf.\p"
	.string "Pokémon can be counted on to do so\n"
	.string "much!$"

Route118_Text_RouteSignMauville:
	.string "Route 118\n"
	.string "{LEFT_ARROW} Mauville City$"

Route118_Text_RouteSign119:
	.string "Route 118\n"
	.string "{UP_ARROW} Route 119$"

