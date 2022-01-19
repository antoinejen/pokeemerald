RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, RustboroCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_RUSTBORO_EGG, RustboroCity_House1_EventScript_ReceivedEgg
	msgbox RustboroCity_House1_Text_GiveEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, RustboroCity_House1_EventScript_NoRoomForEgg
	setflag FLAG_RECEIVED_RUSTBORO_EGG
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_House1_Text_ReceivedTheEgg
	waitfanfare
	switch VAR_STARTER_MON
	case 0, RustboroCity_House1_EventScript_GetEggPsyduck
	case 1, RustboroCity_House1_EventScript_GetEggVoltorb
	case 2, RustboroCity_House1_EventScript_GetEggPonyta
	release
	end

RustboroCity_House1_EventScript_GetEggPsyduck::
	giveegg SPECIES_PSYDUCK
	msgbox RustboroCity_House1_Text_YoullNeedPatienceToHatchIt, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_GetEggVoltorb::
	giveegg SPECIES_VOLTORB
	msgbox RustboroCity_House1_Text_YoullNeedPatienceToHatchIt, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_GetEggPonyta::
	giveegg SPECIES_PONYTA
	msgbox RustboroCity_House1_Text_YoullNeedPatienceToHatchIt, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_ReceivedEgg::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_DeclineEgg::
	msgbox RustboroCity_House1_Text_AsYouWish, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NoRoomForEgg::
	msgbox RustboroCity_House1_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "Huh? My Pokémon is cute?\n"
	.string "Sure, I knew that.\p"
	.string "But if you really want, I'm willing\n"
	.string "to trade it to you.\p"
	.string "I'll trade you my {STR_VAR_2} for\n"
	.string "a {STR_VAR_1} if you want.$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "Eheheh…\n"
	.string "Please be good to my Pokémon.$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "Huh? That doesn't look anything like\n"
	.string "a {STR_VAR_1} to me.$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "Oh, if you don't want to, that's okay.\n"
	.string "But my Pokémon is cute, you know…$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "Any Pokémon can be cute if you raise\n"
	.string "it with care and kindness.$"

RustboroCity_House1_Text_GiveEgg:
	.string "I am from the Kanto region.\n"
	.string "I came here to Hoenn to go sightseeing.\p"
	.string "You look like a new Trainer to me.\n"
	.string "I would be happy to help you in your\l"
	.string "journey.\p"
	.string "How about this Egg that I brought from\n"
	.string "home?$"

RustboroCity_House1_Text_AsYouWish:
	.string "Oh, if you don't want to, that's okay.\n"
	.string "Best of luck in your travels!$"

RustboroCity_House1_Text_NoRoomForThisEgg:
	.string "Oh? It looks like your party is full.\n"
	.string "There's no room for this Egg…$"

RustboroCity_House1_Text_YoullNeedPatienceToHatchIt:
	.string "You'll need patience to hatch it,\n"
	.string "but I'm sure it will be reliable.$"

RustboroCity_House1_Text_ReceivedTheEgg:
	.string "{PLAYER} received an Egg.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "In all sorts of places, there are all\n"
	.string "sorts of Pokémon and people.\p"
	.string "I find that fascinating, so I go to all\n"
	.string "sorts of places.$"

