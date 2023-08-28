.set LOCALID_RED, 1

MeteorFalls_RedsCave_MapScripts::
	.byte 0

MeteorFalls_RedsCave_EventScript_Red::
	lock
	goto_if_set FLAG_DEFEATED_RED, MeteorFalls_RedsCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_RED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RED, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_RED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_RedsCave_Text_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_RED, MeteorFalls_RedsCave_Text_RedDefeat
	setflag FLAG_DEFEATED_RED
	release
	end

MeteorFalls_RedsCave_EventScript_Defeated::
	msgbox MeteorFalls_RedsCave_Text_Defeated, MSGBOX_DEFAULT
	releaseall
	end

MeteorFalls_RedsCave_Text_Defeated:
	.string "… … … … … …\n"
	.string "… … … … … …$"

MeteorFalls_RedsCave_Text_Intro:
	.string "… … … … … …?$"

MeteorFalls_RedsCave_Text_RedDefeat:
	.string "…!$"
