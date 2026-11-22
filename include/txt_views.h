/* The text pointer table and the indices of its named texts (the source of truth; edit by hand).

   The original's 0x143a1c0 is char *txt_Ptrs[0x4800]: txt_LoadTextFile stores into slot i the address of text i
   in its file's buffer, and the game reads a text as txt_Ptrs[i] (io_PrintText / txt_Format take the index
   itself). The first 122 slots are the d2 engine's strings (d2.c reads txt_Ptrs[k] too).

   Every slot holds a char *. The constants below name the slots the code reads by a fixed index: TXT_X is the
   index of one text, a range is its first index TXT_X with TXT_X_N the slots up to the next named text (the
   extent our earlier views had, not a count the original states), read txt_Ptrs[TXT_X + i]. TXT_OBJECT_NAMES
   holds two slots per object kind (the name at TXT_OBJECT_NAMES + 2 * kind), TXT_BUILDING_NAMES fourteen per
   building kind (the kind's name at TXT_BUILDING_NAMES + 14 * kind - 2). The slots no code names are not listed.
   (The names were byte-offset views of txt_Ptrs before, `*(char **)((char *)txt_Ptrs + 0x22c)`: they assumed
   4-byte pointers, and some read a slot as int or int[]; plain indexing reads the same slot on any target.) */
#ifndef TXT_VIEWS_H
#define TXT_VIEWS_H

extern char *txt_Ptrs[0x4800];    /* 0x143a1c0, each text in its file's buffer */

#define TXT_NETWORK_SYNC_WAIT                0x7a
#define TXT_GATE_ITEM_SUFFIX                 0x83      /* text 0x83: what sv_DrawGateName appends to a gate's item name (a guess from the use) */
#define TXT_GATE_PLACE_SUFFIX                0x84      /* text 0x84: what sv_DrawGateName appends to a room / building kind name (a guess from the use) */
#define TXT_SPEED_HOST_ONLY                  0x86      /* the status text ai_SpeedKeys shows to a network client that presses a speed key (only the host sets the speed); its wording is unknown */
#define TXT_CONTACT_MERCENARY_BOOK           0x8a      /* the hover text of the mercenary book ob_SOELDNERBUCH (ai_MercenaryBookContact); the wording is unknown */
#define TXT_TRIBUNE                          0x8b      /* text 0x8b: the name plate text of the market stand ob_TRIBUENE (ai_MarketStandListener) */
#define TXT_CONTACT_PARCHMENT                0x8d      /* the text the ub_INFORMATIONSPERGAMENT plate of the room 0x14c listener shows (ai_GuildHallListener); the wording is unknown */
#define TXT_INFO_PANEL_BUTTONS               0xf2
#define TXT_INFO_PANEL_BUTTONS_N             7
#define TXT_HONOUR_TITLES                    0x114
#define TXT_HONOUR_TITLES_N                  2
#define TXT_PSEUDO_CHAR_NAME                 0x116
#define TXT_FEMALE_HONOUR_TITLE              0x11f     /* the honour title a female player's name line shows (the male one is TXT_HONOUR_TITLES + 1) */
#define TXT_JOB_NAMES                        0x130
#define TXT_JOB_NAMES_N                      221
#define TXT_FEMALE_JOB_NAMES                 (TXT_JOB_NAMES + 0x5f)  /* the female professions (the same job index as TXT_JOB_NAMES) */
#define TXT_PROFESSION_NAMES                 (TXT_JOB_NAMES + 0xbe)  /* the profession names the profession chooser shows, by kind */
#define TXT_TITLE_NAMES                      0x20d
#define TXT_TITLE_NAMES_N                    70
#define TXT_OFFICE_NAMES                     0x253
#define TXT_OFFICE_NAMES_N                   84
#define TXT_MALE_FIRST_NAMES                 0x2a7
#define TXT_MALE_FIRST_NAMES_N               197
#define TXT_FEMALE_FIRST_NAMES               0x36c
#define TXT_FEMALE_FIRST_NAMES_N             130
#define TXT_FAMILY_NAMES                     0x3ee
#define TXT_FAMILY_NAMES_N                   152
#define TXT_FAITH_NAMES                      0x486
#define TXT_FAITH_NAMES_N                    3
#define TXT_SEX_NAMES                        0x489
#define TXT_SEX_NAMES_N                      4
#define TXT_NO_RELATIVE                      0x48d
#define TXT_BUILDING_NAMES                   0x490
#define TXT_BUILDING_NAMES_N                 1304
#define TXT_OBJECT_NAMES                     0x9a8
#define TXT_OBJECT_NAMES_N                   100
#define TXT_CONTACT_PERSONNEL_BOOK           0xa0c
#define TXT_CONTACT_INFORMATION              0xa5e     /* the hover text of the contact_INFORMATION plate and of ob_INFORMATIONSPERGAMENT (both open ai_SpyReportsWindow) */
#define TXT_CONTACT_MASTER_LETTER            0xa82
#define TXT_CONTACT_POND                     0xb64
#define TXT_CONTACT_FLY_GLASS                0xb66
#define TXT_CONTACT_TERRARIUM                0xb6e
#define TXT_FIGHT_PAUSED                     0x112d
#define TXT_WEAPON_EMPTY_15E                 0x11b9
#define TXT_WEAPON_EMPTY_174                 0x11ba
#define TXT_WEAPON_EMPTY_176                 0x11bb
#define TXT_CLICK_NO_GROUND                  0x11bc
#define TXT_FIGHT_BUTTON                     0x11bd
#define TXT_AUCTION_NOTE_LOCAL               0x11bf
#define TXT_AUCTION_NOTE_NET                 0x11c0
#define TXT_BIRTH_NOTE_TAIL                  0x11c2
#define TXT_EXEC_NOTE_TAIL                   0x11c9
#define TXT_DUEL_NOTE_TAIL                   0x11cd
#define TXT_DUEL_DEATH_NEWS                  0x11ce
#define TXT_DUEL_HELD_NEWS                   0x11cf
#define TXT_UNK_11E2                         0x11e2
#define TXT_UNK_11E5                         0x11e5
#define TXT_UNK_11E8                         0x11e8
#define TXT_GUILD_PRICE_RAISE                0x1645    /* text 0x1645: the raise button of ai_GuildLevel1Window */
#define TXT_GUILD_PRICE_LOWER                0x1646    /* text 0x1646: the lower button of ai_GuildLevel1Window */
#define TXT_GUILD_PRICE_CLOSE                0x1647    /* text 0x1647: the close button of ai_GuildLevel1Window */
#define TXT_GUILD_POWER_PICK                 0x165f    /* text 0x165f: the map-pick prompt of ai_GuildGiftEntry and the head of its callback's window */
#define TXT_GUILD_LEVEL_2_PICK               0x166c    /* text 0x166c: the column menu prompt of ai_GuildLevel3Entry for the second offices 0x1f / 0x21 */
#define TXT_GUILD_LEVEL_3_POWER_PICK         0x1676    /* text 0x1676: the column menu prompt of ai_GuildLevel3Entry for the second office 0x20 */
#define TXT_GUILD_LEVEL_3_PICK               0x167e    /* text 0x167e: the character pick prompt of ai_GuildLevel3Entry for the second office 0x1e */
#define TXT_GUILD_POWER_USED                 0x1686    /* text 0x1686: the town hall's guild power is used already (amt_CanUseMayorPower2 returns -1) */
#define TXT_CONTACT_RAW_MATERIAL_SEARCH      0x17fd
#define TXT_CONTACT_DICE_GAME                0x1873    /* the hover text of the contact_WUERFELSPIEL plate (the tavern listener 0x599af0) */
#define TXT_CONTACT_STAMMTISCH               0x188b    /* the hover text of the contact_STAMMTISCH plate (0x599af0) */
#define TXT_CONTACT_DARK_CORNER              0x18ab    /* the hover text of the ob_DUNKLE_ECKE plate (0x599af0) */
#define TXT_CONTACT_INDULGENCE               0x195f
#define TXT_CONTACT_TOP_5                    0x196a
#define TXT_CONTACT_DUNGEON_PLAN             0x19ac
#define TXT_CONTACT_BRIBE                    0x19b0    /* text 0x19b0: the plate text of the bribe contact contact_BESTECHEN (ai_DungeonBribeListener) */
#define TXT_CONTACT_KIDNAP                   0x19b7    /* the hover text of the contact_ENTFUEHREN plate (ai_KidnapContact -> ai_KidnapStart) */
#define TXT_KIDNAP_MESSAGE                   0x19bb    /* text 0x19bb: the message ai_KidnapStart shows when the building already has a kidnap event */
#define TXT_CONTACT_RANSOM                   0x19c3    /* the hover text of the contact_LOESEGELD plate (ai_KidnapContact -> ai_RansomWindow) */
#define TXT_CONTACT_BURGLARY                 0x19e1    /* the hover text of the contact_EINBRUCH plate of the thieves' guild hall (ai_ThievesGuildListener) */
#define TXT_MAP_PICK_PROMPT                  0x19ed    /* the prompt text the burglar-guild map picks (ai_OpenPickpocket, ai_AttackStart) pass to ai_MapPick */
#define TXT_CONTACT_SPY_BUILDING             0x19f5    /* the hover text of the contact_GEBAEUDE_AUSSPIONIEREN plate (ai_ThievesGuildListener -> ai_EspionageStart) */
#define TXT_OFFICE_NONE_OPEN                 0x1a02    /* text 0x1a02: ai_OfficeApplicationWindow's message when no office is open to the player */
#define TXT_OFFICE_NO_RANK                   0x1a03    /* text 0x1a03: ai_OfficeApplicationWindow's message when the player's AICHAR.level is below 2 (the slots 0x1a04 / 0x1a05 follow: 0x1a04 formats an office button) */
#define TXT_OFFICE_ALL_FULL                  0x1a06    /* text 0x1a06: ai_OfficeApplicationWindow's message when the offices open to the player all hold 4 applicants */
#define TXT_OFFICE_APPLY                     0x1a08    /* text 0x1a08: the apply button of ai_OfficeApplicantsWindow */
#define TXT_OFFICE_COLUMN                    0x1a09    /* text 0x1a09: the button of ai_OfficeApplicantsWindow that opens the office's column in the special-amount list */
#define TXT_OFFICE_INFO                      0x1a0a    /* text 0x1a0a: the button of ai_OfficeApplicantsWindow that opens the office's info (ai_AmountInfoWindow) */
#define TXT_OFFICE_APPLIED                   0x1a0d    /* text 0x1a0d: ai_OfficeApplicationWindow's message after a successful application */
#define TXT_CONTACT_MAP_TABLE                0x1a10    /* text 0x1a10: the plate text of the map table ob_KARTENTISCH (ai_MapTableContact) */
#define TXT_NO_CHARACTER                     0x1a42
#define TXT_CONTACT_TARGET                   0x1a43    /* the hover text of the ob_ZIELSCHEIBE plate (its click opens ai_TrainingWindow) */
#define TXT_CONTACT_TRAINING                 0x1a44    /* the hover text of the ob_STROHPUPPE and contact_NACHT plates (both open ai_TrainingWindow) */
#define TXT_CONTACT_WINE_CELLAR              0x1a4b
#define TXT_CONTACT_MISTRESS                 0x1a4e
#define TXT_CONTACT_PATROL                   0x1a67    /* the hover text of the contact_PATROL plate (ai_CityWatchListener); the wording is unknown */
#define TXT_PATROL_PICK_PROMPT               0x1a68    /* the prompt text of the city watch patrol map pick (ai_PatrolStart) */
#define TXT_RAID_PICK_PROMPT                 0x1a6c    /* the prompt text of the city watch raid map pick (ai_RaidStart) */
#define TXT_CONTACT_WATCH_PLAN               0x1a6e    /* the hover text of the ob_WACHPLAN plate (ai_CityWatchListener); the wording is unknown */
#define TXT_WATCH_PLAN_PICK_PROMPT           0x1a6f    /* the prompt text of the city watch plan map pick (ai_WatchPlanStart) */
#define TXT_CONTACT_CUSTOMS_BOX              0x1a71    /* the hover text of the ob_ZOLLKASSE and ob_ZOLLKASSE_MIT_GEHEIMFACH plates (ai_CityWatchListener); the wording is unknown */
#define TXT_ARREST_PICK_PROMPT               0x1a72    /* the prompt text of the city watch arrest map pick (ai_ArrestStart -> ai_ArrestWindow); the wording is unknown */
#define TXT_CONTACT_RAID                     0x1a82    /* the hover text of the contact_RAUBUEBERFALL plate (its click opens ai_OpenRaid) */
#define TXT_BRIBE_PICK                       0x1a8a    /* the pick prompt ai_OpenBribe hands to ai_MapPick for the bribe */
#define TXT_BREAK_IN_PICK                    0x1a94    /* the pick prompt ai_BreakInWindow hands to ai_MapPick for the burglar-guild break-in */
#define TXT_DEATH_TREE_CAPTION               0x1ab2
#define TXT_MALE                             0x1ad5
#define TXT_FEMALE                           0x1ad6
#define TXT_FAITH_0                          0x1ad8
#define TXT_FAITH_1                          0x1ad9
#define TXT_FAMILY_MODEL_NAMES               0x1af0    /* the nine template model names main_ChooseFamily places (the family figure k) */
#define TXT_FAMILY_MODEL_NAMES_N             9
#define TXT_LOAD_GAME                        0x1c5c
#define TXT_SAVE_GAME                        0x1c5d
#define TXT_GAME_OPTIONS                     0x1c5e
#define TXT_GFX_OPTIONS                      0x1c5f
#define TXT_SFX_OPTIONS                      0x1c60
#define TXT_LEAVE_GAME                       0x1c61
#define TXT_BACK                             0x1c62
#define TXT_SPEED_NAMES                      0x1c82
#define TXT_SPEED_NAMES_N                    10
#define TXT_DIFFICULTY_TEXTS                 0x1c8c
#define TXT_DIFFICULTY_TEXTS_N               38
#define TXT_SCENE_PARTY_SYNC                 0x1cb2
#define TXT_SCENE_PARTY_WAIT                 0x1cb3    /* the status text while the scene party's members answer (cm_RunSceneParty; a guess from the use) */
#define TXT_STATUS_SEND_GAME                 0x1cb4
#define TXT_STATUS_RECEIVE_GAME              0x1cb5
#define TXT_STATUS_SETUP_GAME                0x1cb6
#define TXT_STATUS_LOCAL_DATA                0x1cb7
#define TXT_STATUS_FORMAT                    0x1cb8
#define TXT_QUICK_SAVE_NO_PLAYER             0x1cb9
#define TXT_QUICK_SAVE_DISABLED              0x1cba
#define TXT_SAVE_WAIT                        0x1cbb
#define TXT_CHAT_CONSOLE_SLIDER              0x1cc2
#define TXT_EMPTY_SLOT_NAME_FORMAT           0x1cc8
#define TXT_LOAD_GAME_CONFIRM                0x1cc9
#define TXT_SAVE_PROGRESS                    0x1cca
#define TXT_SAVE_OVERWRITE                   0x1ccb
#define TXT_DEFAULT_FILE_NAME                0x1ccd
#define TXT_MESSAGE_FILTER_TEXTS             0x1cd0
#define TXT_MESSAGE_FILTER_TEXTS_N           666
#define TXT_PANEL_BTN_BUILD                  0x1f6a
#define TXT_PANEL_BTN_OWN                    0x1f6b
#define TXT_PANEL_BTN_KIND_1E                0x1f6c
#define TXT_PANEL_BTN_FOREIGN                0x1f6d
#define TXT_PANEL_BTN_ITEM_OWN               0x1f6e
#define TXT_PANEL_BTN_ITEM                   0x1f6f
#define TXT_EINKAUF                          0x1f70
#define TXT_CONTACT_GELAGE                   0x1f72    /* the hover text of the contact_GELAGE plate (ai_GelageWindow) */
#define TXT_CONTACT_STORAGE                  0x1f74
#define TXT_CONTACT_PRODUCTION               0x1f76    /* the hover text of the production plates (contact_PRODUKTION / _METALL; ai_ProductionGoodsWindow) */
#define TXT_CONTACT_TRANSPORT                0x1f78
#define TXT_CONTACT_ATTACK                   0x1f7a    /* the hover text of the contact_ANGRIFF plate (its click opens ai_OpenPickpocket) */
#define TXT_CONTACT_AMBUSH                   0x1f7c    /* the hover text of the contact_AUF_LAUER_LEGEN plate (its click opens ai_BreakInWindow) */
#define TXT_CONTACT_EQUIP                    0x1f7e    /* the hover text of the AUSRUESTEN plate and of the weapon stand ub_STAENDER_WAFFEN (both open ai_EquipWindow); the wording is unknown */
#define TXT_CONTACT_SPY                      0x1f88    /* the hover text of the contact_GEBAEUDE_AUSSPIONIEREN plate (its click opens ai_OpenSpying) */
#define TXT_CONTACT_RAZZIA                   0x1f90    /* the hover text of the contact_RAZZIA plate of the room 0x14c listener (ai_GuildHallListener); the wording is unknown */
#define TXT_CONTACT_REGENERATION             0x1f92    /* the hover text of the contact_REGENERATION plate (its click opens ai_TrainingWindow) */
#define TXT_CONTACT_EXTORT                   0x1f94    /* the hover text of the contact_SCHUTZGELD_ERPRESSEN plate (its click opens ai_OpenBribe) */
#define TXT_CONTACT_PICKPOCKET               0x1f96    /* the hover text of the contact_TASCHENDIEBSTAHL plate (ai_ThievesGuildListener -> ai_PickpocketGangWindow) */
#define TXT_CONTACT_FAR_BUY                  0x1f9a    /* the hover text of the FERNEINKAUF plate (ai_FarTradeContact) */
#define TXT_CONTACT_SELL                     0x1fa2    /* the hover text of the VERKAUF plate (ai_FarTradeContact) */
#define TXT_EINKAUF_SKRIPTE                  0x1faa
#define TXT_CONTACT_PRODUCTION_MIXING        0x1fb4    /* the hover text of the contact_PRODUKTION_MISCHEN plate (ai_MixingContact) */
#define TXT_CONTACT_PRODUCTION_PERFUMERY     0x1fb6
#define TXT_CONTACT_EXTRACT                  0x1fba    /* the hover text of the extraction plate (contact_ABBAUEN / contact_ABBAU, ai_MiningContact); the wording is unknown */
#define TXT_EINKAUF_METALL                   0x1fbc
#define TXT_EINKAUF_STEIN                    0x1fbe
#define TXT_CONTACT_SEARCH_ORE               0x1fc4    /* the hover text of the ore-search plate (contact_SUCHEN_ERZ, ai_MiningContact); the wording is unknown */
#define TXT_CONTACT_SEARCH_STONE             0x1fc6    /* the hover text of the stone-search plate (contact_SUCHEN_STEIN, ai_StoneKontorContact) */
#define TXT_CONTACT_PRODUCTION_SMITHY        0x1fd2    /* the hover text of the contact_PRODUKTION_SCHMIEDEN plate (ai_SmithyContact) */
#define TXT_CONTACT_PRODUCTION_STONECUTTER   0x1fd4    /* the hover text of the contact_PRODUKTION_STEINMETZ plate (ai_StonecutterContact) */
#define TXT_CONTACT_PRODUCTION_CARPENTER     0x1fd6    /* the hover text of the contact_PRODUKTION_TISCHLER plate (ai_CarpenterContact) */
#define TXT_EINKAUF_HOLZ                     0x1fd8
#define TXT_CONTACT_PRODUCTION_WOOD          0x1fda    /* the hover text of the contact_PRODUKTION_HOLZ plate */
#define TXT_CONTACT_PRODUCTION_BREWING       0x1fdc    /* the hover text of the contact_PRODUKTION_BRAUEN plate (ai_BreweryContact) */
#define TXT_BUILDING_CLOSED                  0x2055    /* text 0x2055: the title of the message ai_MayEnterBuilding shows when a building is closed (its texts 0x2056 .. 0x2058 follow) */
#define TXT_TIP_TEXTS                        0x209c    /* the 27 tip texts the tips event 0x84 shows (he.c 0x567c00; filled by txt_LoadTextFile) */
#define TXT_TIP_TEXTS_N                      52
#define TXT_PILLORY_PUNISHMENT               0x20d0    /* text 0x20d0 ("_MESSAGES_PRANGER+0", "Eure Prangerstrafe..."): the AP event name the pillory-punishment event 0x5c registers */
#define TXT_DLG_TITLE                        0x387f
#define TXT_DLG_LABEL_104                    0x3880
#define TXT_DLG_LABEL_105                    0x3881
#define TXT_AMOUNT_UNIT                      0x3fe8
#define TXT_CONTACT_BREAK_OUT                0x3fef    /* the hover text of the contact_AUSBRECHEN plate (ai_KidnapContact -> ai_HostageEscape) */
#define TXT_ALCHEMIST_FIRST_NAMES            0x417a
#define TXT_ALCHEMIST_FIRST_NAMES_N          25
#define TXT_ALCHEMIST_FAMILY_NAMES           0x4193
#define TXT_ALCHEMIST_FAMILY_NAMES_N         30
#define TXT_CONTACT_BLOOD_REVENGE            0x41b1
#define TXT_CONTACT_CURSE                    0x41c0
#define TXT_CONTACT_THEATRE                  0x41f3
#define TXT_CONTACT_HOMAGE                   0x4206
#define TXT_CONTACT_CHAT                     0x4226
#define TXT_TAILOR_BLOCKED                   0x4228
#define TXT_TAILOR_AMOUNT                    0x422a
#define TXT_CONTACT_PRODUCTION_TAILOR        0x4231
#define TXT_CONTACT_CARD_GAME                0x4237
#define TXT_NET_PLAYERS                      0x4285
#define TXT_JOB_LABEL                        0x4288    /* the label of the lobby info window's profession line */
#define TXT_FAITH_LABEL                      0x4289    /* the label of the lobby info window's faith line */
#define TXT_LOBBY_READY                      0x428a    /* text 0x428a: the label of the lobby's ready button (lobby_AddButtons, sv_ButtonRow) */
#define TXT_LOBBY_CHARACTER                  0x428b    /* text 0x428b: the label of the lobby's character button (the player / profession pickers) */
#define TXT_LOBBY_LEAVE                      0x428c    /* text 0x428c: the label of the lobby's leave button */
#define TXT_READY_MARK                       0x428d    /* the ready marker lobby_ShowPlayers appends to a ready player's line */
#define TXT_CHAT_PRIVATE                     0x428e    /* the mark lobby_ShowChat puts after the sender's name of a private chat line */
#define TXT_PANEL_BTN_CART                   0x42d9
#define TXT_ROUTE_LOAD_HEAD                  0x42da
#define TXT_ROUTE_UNLOAD_HEAD                0x42db
#define TXT_ROUTE_EDIT_POINT                 0x42dc
#define TXT_ROUTE_ADD_POINT                  0x42dd
#define TXT_ROUTE_SETTINGS                   0x42de
#define TXT_ROUTE_OK                         0x42df
#define TXT_ROUTE_DELETE_POINT               0x42e1
#define TXT_ROUTE_NEW                        0x42e3
#define TXT_PATROL_LEVEL_0                   0x42e5
#define TXT_PATROL_LEVEL_1                   0x42e6
#define TXT_PATROL_LEVEL_2                   0x42e7
#define TXT_PATROL_LEVEL_3                   0x42e8
#define TXT_PATROL_LEVEL_4                   0x42e9
#define TXT_PATROL_TOGGLE                    0x42ee
#define TXT_PATROL_TOGGLE_N                  14
#define TXT_PANEL_PERSONS                    0x42fc

#endif
