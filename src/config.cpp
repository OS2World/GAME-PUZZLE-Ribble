//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include "config.h"
#define LANG_NO_TABLES
#include "lang.h"
#include <stdio.h>

const char* AppName = "Ribble_V1.1";


RibbleConfig::RibbleConfig()
{
  cellWidth = 64;
  visWidth = 14;
  centreXoff = visWidth >> 1;
  stepX = 4;
  controlType = Arrow;
  leftKey = 'z';
  rightKey = 'x';
  upKey = '\'';
  downKey = '/';
  refreshRate = 60;
  saveConfig = FALSE;
  currentLang = LANG_ENGLISH;
}

RibbleConfig::~RibbleConfig()
{
}

void
RibbleConfig::LoadConfig(void)
{
  LoadInt("cellWidth", cellWidth);
  LoadInt("visWidth", visWidth);
  LoadInt("centreXoff", centreXoff);
  LoadInt("stepX", stepX);
  LoadInt("controlType", controlType);
  LoadInt("leftKey", leftKey);
  LoadInt("rightKey", rightKey);
  LoadInt("upKey", upKey);
  LoadInt("downKey", downKey);
  LoadInt("refreshRate", refreshRate);
  LoadInt("saveConfig", saveConfig);
  LoadInt("current_lang", currentLang);
  if (currentLang < 0 || currentLang >= NUM_LANGUAGES)
    currentLang = LANG_ENGLISH;
}

void
RibbleConfig::SaveConfig(void)
{
  if (saveConfig)
    {
      StoreInt("cellWidth", cellWidth);
      StoreInt("visWidth", visWidth);
      StoreInt("centreXoff", centreXoff);
      StoreInt("stepX", stepX);
      StoreInt("controlType", controlType);
      StoreInt("leftKey", leftKey);
      StoreInt("rightKey", rightKey);
      StoreInt("upKey", upKey);
      StoreInt("downKey", downKey);
      StoreInt("refreshRate", refreshRate);
    }
  StoreInt("saveConfig", saveConfig);
}

void
RibbleConfig::SetLang(int _val)
{
  if (_val < 0 || _val >= NUM_LANGUAGES)
    return;
  currentLang = _val;
  StoreInt("current_lang", currentLang);
}

void
RibbleConfig::StoreInt(char* _key, int _val)
{
  PrfWriteProfileData(HINI_USERPROFILE,
                      (PSZ)AppName,
                      (PSZ)_key,
                      (PVOID)&_val,
                      sizeof(_val));
}

void
RibbleConfig::LoadInt(char* _key, int& _fill)
{
  ULONG size = sizeof(_fill);
  int data;

  BOOL success = PrfQueryProfileData(HINI_USERPROFILE,
                                     (PSZ)AppName,
                                     (PSZ)_key,
                                     (PVOID)&data,
                                     &size);
  if (success == TRUE && size == sizeof(_fill))
    _fill = data;
}

void
RibbleConfig::LoadScoreItem(int _num, ScoreItem* _dest)
{
  char keyname[128];
  sprintf(keyname, "ScoreLine%d", _num);

  ScoreItem data;
  ULONG size = sizeof(data);

  BOOL success = PrfQueryProfileData(HINI_USERPROFILE,
                                     (PSZ)AppName,
                                     (PSZ)keyname,
                                     (PVOID)&data,
                                     &size);

  if (success == TRUE && size == sizeof(data))
    *_dest = data;
  else
    {
      _dest->score = 0;
      strcpy(_dest->text, "JRS & DJN");
    }
}

void
RibbleConfig::SaveScoreItem(int _num, ScoreItem* _dest)
{
  char keyname[128];
  sprintf(keyname, "ScoreLine%d", _num);

  PrfWriteProfileData(HINI_USERPROFILE,
                      (PSZ)AppName,
                      (PSZ)keyname,
                      (PVOID)_dest,
                      sizeof(*_dest));
}

