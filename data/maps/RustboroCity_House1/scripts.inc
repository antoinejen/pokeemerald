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
	goto_if_set FLAG_RECEIVED_RUSTBORO_MON, RustboroCity_House1_EventScript_ReceivedMon
	msgbox RustboroCity_House1_Text_GiveMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineMon
	switch VAR_STARTER_MON
	case 0, RustboroCity_House1_EventScript_GetPsyduck
	case 1, RustboroCity_House1_EventScript_GetVoltorb
	case 2, RustboroCity_House1_EventScript_GetPonyta
	end

RustboroCity_House1_EventScript_GetPsyduck::
	setvar VAR_TEMP_1, SPECIES_PSYDUCK
	bufferspeciesname STR_VAR_3, SPECIES_PSYDUCK
	givemon SPECIES_PSYDUCK, 10, ITEM_NONE
	goto_if_eq VAR_RESULT, 0, RustboroCity_House1_EventScript_ReceivePokemonParty
	goto_if_eq VAR_RESULT, 1, RustboroCity_House1_EventScript_ReceivePokemonPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_House1_EventScript_GetVoltorb::
	setvar VAR_TEMP_1, SPECIES_VOLTORB
	bufferspeciesname STR_VAR_3, SPECIES_VOLTORB
	givemon SPECIES_VOLTORB, 10, ITEM_NONE
	goto_if_eq VAR_RESULT, 0, RustboroCity_House1_EventScript_ReceivePokemonParty
	goto_if_eq VAR_RESULT, 1, RustboroCity_House1_EventScript_ReceivePokemonPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_House1_EventScript_GetPonyta::
	setvar VAR_TEMP_1, SPECIES_PONYTA
	bufferspeciesname STR_VAR_3, SPECIES_PONYTA
	givemon SPECIES_PONYTA, 10, ITEM_NONE
	goto_if_eq VAR_RESULT, 0, RustboroCity_House1_EventScript_ReceivePokemonParty
	goto_if_eq VAR_RESULT, 1, RustboroCity_House1_EventScript_ReceivePokemonPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_House1_EventScript_ReceivedPokemonFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_House1_Text_PlayerReceivedPokemon
	waitmessage
	waitfanfare
	return

RustboroCity_House1_EventScript_ReceivePokemonParty::
	call RustboroCity_House1_EventScript_ReceivedPokemonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_TakeCare
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_House1_EventScript_TakeCare
	end

RustboroCity_House1_EventScript_ReceivePokemonPC::
	call RustboroCity_House1_EventScript_ReceivedPokemonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_SendPokemonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_House1_EventScript_SendPokemonToPC
	end

RustboroCity_House1_EventScript_SendPokemonToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_House1_EventScript_TakeCare
	end

RustboroCity_House1_EventScript_TakeCare:
	setflag FLAG_RECEIVED_RUSTBORO_MON
	msgbox RustboroCity_House1_Text_TakeCare, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_ReceivedMon::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_DeclineMon::
	msgbox RustboroCity_House1_Text_AsYouWish, MSGBOX_DEFAULT
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

RustboroCity_House1_Text_GiveMon:
	.string "I am from the Kanto region.\n"
	.string "I came here to Hoenn to go sightseeing.\p"
	.string "You look like a new Trainer to me.\n"
	.string "I would be happy to help you in your\l"
	.string "journey.\p"
	.string "How about I give you this Pokémon that\n"
	.string "I brought from home?$"

RustboroCity_House1_Text_AsYouWish:
	.string "Oh, if you don't want to, that's okay.\n"
	.string "Best of luck in your travels!$"

RustboroCity_House1_Text_PlayerReceivedPokemon:
	.string "{PLAYER} received {STR_VAR_3}!$"

RustboroCity_House1_Text_TakeCare:
	.string "Please take care of it.\n"
	.string "I hope it will help you in your journey.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "In all sorts of places, there are all\n"
	.string "sorts of Pokémon and people.\p"
	.string "I find that fascinating, so I go to all\n"
	.string "sorts of places.$"
