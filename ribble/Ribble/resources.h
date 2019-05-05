//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Resources_h
#define _Resources_h

// Bitmap identifiers

#define BMP_LowestID              100
#define BMP_Empty                 100
#define BMP_Boulder               101
#define BMP_BlueWall              102
#define BMP_Diamond               103
#define BMP_Earth                 104
#define BMP_RedWall               105
#define BMP_RedWallN              106
#define BMP_RedWallNE             107
#define BMP_RedWallSE             108
#define BMP_RedWallSW             109
#define BMP_RedWallNW             110
#define BMP_Spirit                111
#define BMP_RibbleStatic          112
#define BMP_RedWallS              113
#define BMP_RedWallE              114
#define BMP_RedWallW              115
#define BMP_WalkRight1            116
#define BMP_WalkRight2            117
#define BMP_WalkRight3            118
#define BMP_WalkLeft1             119
#define BMP_WalkLeft2             120
#define BMP_WalkLeft3             121
#define BMP_Spirit1               122
#define BMP_Egg                   123
#define BMP_CrackedEgg            124
#define BMP_SpiritMask            125
#define BMP_Spirit1Mask           126
#define BMP_Cage                  127
#define BMP_Safe                  128
#define BMP_Key                   129
#define BMP_RibbleV1              130
#define BMP_RibbleV2              131
#define BMP_Edit                  132
#define BMP_EditMask              133
#define BMP_Slither               134
#define BMP_Slither1              135
#define BMP_SlitherMask           136
#define BMP_SlitherMask1          137
#define BMP_Grave                 138
#define BMP_Title                 139
#define BMP_Teleport              140
#define BMP_Teleport1             141
#define BMP_Teleport2             142
#define BMP_Teleport3             143
#define BMP_Teleport4             144
#define BMP_Bomb                  145
#define BMP_BombLive1             146
#define BMP_BombLive2             147
#define BMP_Flame1                148
#define BMP_Flame2                149
#define BMP_Flame3                150
#define BMP_HighestID             200

#define BMP_Tribble                 30001
#define BMP_TribbleNormal           30002
#define BMP_TribbleAntennae1        30003
#define BMP_TribbleAntennae2        30004
#define BMP_TribbleAntennae3        30005
#define BMP_TribbleAntennae4        30006
#define BMP_TribbleAntennae5        30007
#define BMP_TribbleAntennae6        30008
#define BMP_TribbleAntennae7        30009
#define BMP_TribbleBlink1           30010
#define BMP_TribbleBlink2           30011
#define BMP_TribbleBlink3           30012
#define BMP_TribbleBlink4           30013
#define BMP_TribbleBlink5           30014
#define BMP_TribbleEyeRoll1         30015
#define BMP_TribbleEyeRoll2         30016
#define BMP_TribbleEyeRoll3         30017
#define BMP_TribbleEyeRoll4         30018
#define BMP_TribbleEyeRoll5         30019
#define BMP_TribbleEyeRoll6         30020
#define BMP_TribbleEyeRoll7         30021
#define BMP_TribbleEyeRoll8         30022
#define BMP_TribbleEyeRoll9         30023
#define BMP_TribbleSide1            30024
#define BMP_TribbleSide2            30025
#define BMP_TribbleSide3            30026
#define BMP_TribbleSide4            30027
#define BMP_TribbleSide5            30028
#define BMP_TribbleSide6            30029
#define BMP_TribbleSide7            30030
#define BMP_TribbleSide8            30031
#define BMP_TribbleSide9            30032
#define BMP_TribbleSide10           30033
#define BMP_TribbleSide11           30034
#define BMP_TribbleSide12           30035
#define BMP_TribbleJump1            30036
#define BMP_TribbleJump2            30037
#define BMP_TribbleJump3            30038
#define BMP_TribbleJump4            30039
#define BMP_TribbleJump5            30040
#define BMP_TribbleJump6            30041
#define BMP_TribbleJump7            30042
#define BMP_TribbleJump8            30043


// This is a list of all the items that can be stored in
// the map.

enum {
  /*  0*/  ITEM_EMPTY = 0,
  /*  1*/  ITEM_BOULDER,
  /*  2*/  ITEM_BLUEWALL,
  /*  3*/  ITEM_DIAMOND,
  /*  4*/  ITEM_EARTH,
  /*  5*/  ITEM_REDWALL,
  /*  6*/  ITEM_REDWALLN,
  /*  7*/  ITEM_REDWALLNE,
  /*  8*/  ITEM_REDWALLSE,
  /*  9*/  ITEM_REDWALLSW,
  /* 10*/  ITEM_REDWALLNW,
  /* 11*/  ITEM_SPIRIT,
  /* 12*/  ITEM_RIBBLESTATIC,
  /* 13*/  ITEM_REDWALLS,
  /* 14*/  ITEM_REDWALLE,
  /* 15*/  ITEM_REDWALLW,
  /* 16*/  ITEM_WALKRIGHT1,
  /* 17*/  ITEM_WALKRIGHT2,
  /* 18*/  ITEM_WALKRIGHT3,
  /* 19*/  ITEM_WALKLEFT1,
  /* 20*/  ITEM_WALKLEFT2,
  /* 21*/  ITEM_WALKLEFT3,
  /* 22*/  ITEM_SPIRIT1,
  /* 23*/  ITEM_EGG,
  /* 24*/  ITEM_CRACKEDEGG,
  /* 25*/  ITEM_SPIRITMASK,
  /* 26*/  ITEM_SPIRIT1MASK,
  /* 27*/  ITEM_CAGE,
  /* 28*/  ITEM_SAFE,
  /* 29*/  ITEM_KEY,
  /* 30*/  ITEM_RIBBLEV1,
  /* 31*/  ITEM_RIBBLEV2,
  /* 32*/  ITEM_EDIT,
  /* 33*/  ITEM_EDITMASK,
  /* 34*/  ITEM_SLITHER,
  /* 35*/  ITEM_SLITHER1,
  /* 36*/  ITEM_SLITHERMASK,
  /* 37*/  ITEM_SLITHERMASK1,
  /* 38*/  ITEM_GRAVE,
  /* 39*/  ITEM_TITLE,
  /* 40*/  ITEM_TELEPORT,
  /* 41*/  ITEM_TELEPORT1,
  /* 42*/  ITEM_TELEPORT2,
  /* 43*/  ITEM_TELEPORT3,
  /* 44*/  ITEM_TELEPORT4,
  /* 45*/  ITEM_BOMB,
  /* 46*/  ITEM_BOMBLIVE1,
  /* 47*/  ITEM_BOMBLIVE2,
  /* 48*/  ITEM_FLAME1,
  /* 49*/  ITEM_FLAME2,
  /* 50*/  ITEM_FLAME3,

  /*END*/  ITEM_MAXITEM
};

#define IDW_MAIN                  1
#define PTR_MAIN                  2

#define IDM_MainMenu              500

#define IDM_GameMenu              550
#define IDM_GameStart             551
#define IDM_GameAbandon           552
#define IDM_GameOpen              553
#define IDM_GameSave              554
#define IDM_GameSaveAs            555
#define IDM_GameExit              556

#define IDM_EditMenu              600
#define IDM_EditLevel             601
#define IDM_EditOptions           602

#define IDM_ViewMenu              650
#define IDM_ViewMap               651
#define IDM_ViewStatus            652

#define IDM_HelpMenu              700
#define IDM_HelpIndex             701
#define IDM_HelpGeneral           702
#define IDM_HelpUsing             703
#define IDM_HelpKeys              704
#define IDM_HelpProductInfo       705

#define DLG_ProductInfo           1000
#define DLG_SelectLevel           1001
#define DLG_SaveLevel             1002
#define DLG_GameOptions           1003
#define DLG_HiscoreDialog         1004
#define DLG_BadscoreDialog        1005

#define DID_LevelList             1010
#define DID_AuthorText            1011
#define DID_CommentText           1012
#define DID_CollectText           1013
#define DID_TimeText              1014
#define DID_MonstersText          1015
#define DID_DiamondsText          1016
#define DID_TeleportersText       1017
#define DID_SaveAuthorText        1018
#define DID_SaveTitleText         1019
#define DID_SaveCommentText       1020
#define DID_CollectDiamonds       1021
#define DID_CollectEarth          1022
#define DID_CollectMonsters       1023
#define DID_SaveTime              1024
#define DID_SaveLevelFile         1025
#define DID_KeysClassic           1026
#define DID_KeysArrow             1027
#define DID_KeysOther             1028
#define DID_LeftKey               1029
#define DID_RightKey              1030
#define DID_UpKey                 1031
#define DID_DownKey               1032
#define DID_RefreshRate           1033
#define DID_VisibleSize           1034
#define DID_CellSize              1035
#define DID_LeftText              1036
#define DID_RightText             1037
#define DID_UpText                1038
#define DID_DownText              1039
#define DID_OptionsSave         	1040
#define DID_ScoreName             1041
#define DID_BerateText             1042
#define DID_QualifyText            1043
#define DID_AboutButtonGroup	1044


#define ID_HELPTABLE              2000


#endif

