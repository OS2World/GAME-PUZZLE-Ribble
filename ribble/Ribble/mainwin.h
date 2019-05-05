//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _MainWin_h
#define _MainWin_h


class Edit;
class ItemPalette;
class Slither;
class Screen;
class Teleport;
class Man;
class Map;
class RibbleConfig;



class MainWindow : public CWinFramedClient
{
public:

  enum GameState
    {
      PlayGame,
      Teleporting,
      EndLevel,
      GameOver,
      ShowHiscores,
      ShowStatus,
      ShowMap,
      ShowTitle
      };

  MainWindow(HAB hab);
  ~MainWindow();
  void SetupWindow(void);
  MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  MRESULT ProcessCmd(MPARAM mp1, MPARAM mp2);
  void Paint(void);
  MRESULT WMChar(void);
  void WMTimer(void);
  void UpdateScreen(void);
  void InitHelp(void);
  void TermHelp(void);
  BOOL InitGame(int _level = 1, BOOL _realStart = TRUE);
  void EndGame(GameState _newstate = ShowHiscores);
  void HandleThings(void);
  void MoveMonsters(void);
  void DropBoulders(void);
  void RenderScreen(void);
  void RenderStatus(HPS _hps);
  void RenderMap(void);
  void RenderMonsters(void);
  void RenderMan(void);
  void RemoveMonsters(void);
  BOOL RibbleMap(int _x, int _y);
  BOOL RibbleBelow(int _x, int _y);
  void ShowTitleBitmap(HPS hps);
  Map* QueryMap(void) { return map; }
  Man* QueryMan(void) { return man; }
  Edit* QueryEdit(void) { return edit; }
  MonsterList* QueryMonsters(void) { return &monsters; }
  void SetMapItem(int _item);
  void SwapEdit(void);
  void CreateItemPalette(void);
  void RemoveItemPalette(void);
  void ChooseLevel(void);
  Screen* QueryScreen(void) { return screen; }
  void CheckMonsterCrushed(int _x, int _y);
  BOOL CheckManCrushed(int _x, int _y);
  void ToggleMap(void);
  void Scored(int _amount);
  void Died(int _amount = 1);
  void GotTime(int _amount);
  void GotKey(void);
  void EatEarth(void);
  void EatDiamond(void);
  void HandleInsert(void);
  void HandleDelete(void);
  void HandleEscape(void);
  Monster* LocateMonster(int _mx, int _my);
  Teleport* LocateTeleport(int _teleNum);
  Teleport* LocateTeleDest(int _tx, int _ty);
  int QueryHighestTeleNum(void);
  void StartTeleporting(int _tx, int _ty);
  void HandleTeleport(void);
  void RenderPanel(HPS hps = 0);
  void RenderItem(HPS hps, int _off, int _wid, char* title, char* fmt, int val);
  void RenderScore(HPS hps = 0);
  void RenderTime(HPS hps = 0);
  void RenderLives(HPS hps = 0);
  void RenderDiamonds(HPS hps = 0);
  void EnableMenuItems(BOOL _inGame = TRUE);
  void HandleLevelSave(void);
  void OptionsDialog(void);
  RibbleConfig* QueryConfig(void) { return config; }
  void ResetSize(void);
  void StartNextLevel(void);
  void HandleTitle(void);
  void ShowScores(HPS _hps);
  void HandleHiscores(void);
  int QueryNumEarth(void);
  int QueryNumSpirits(void);
  int QueryNumTeleporters(void);
  int QueryNumMonsters(ULONG _name);
  int QueryNumItems(ULONG _name);
  void RestartCurrentLevel(void);


private:

  Edit*         edit;
  Man*          man;
  MonsterList   monsters;
  Screen*       screen;
  Map*          map;
  BOOL          inGame;
  RECTL         border;
  int           time;
  int           score;        // score so far
  int           lives;        // # lives left
  int           diamonds;     // # remaining
  ItemPalette*  itemPalette;
  int           eggHatchCnt;
  int           fizzleCnt;
  int           teleDestX;
  int           teleDestY;
  HWND          hwndMenu;
  HWND          hwndHelp;
  RibbleConfig* config;
  int           teleporting;
  GameState     gamestate;
  int           oldScore;
  BOOL          restartLevel;
};

#endif

