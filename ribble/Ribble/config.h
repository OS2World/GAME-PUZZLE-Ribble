//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Config_h
#define _Config_h

class RibbleConfig
{
public:

  struct ScoreItem
    {
      ScoreItem(void) { score = 0; text[0] = 0; }
      int score;
      char text[64];
    };

  enum ControlType { Arrow = 0,
                     Classic,
                     Other,
                     Unset };

  RibbleConfig(void);
  virtual ~RibbleConfig(void);
  void LoadConfig(void);
  void SaveConfig(void);

  int QueryCellWidth() { return cellWidth; }
  int QueryCellHeight() { return cellWidth; }
  int QueryVisWidth() { return visWidth; }
  int QueryVisHeight() { return visWidth; }
  int QueryCentreXoff() { return centreXoff; }
  int QueryCentreYoff() { return centreXoff; }
  int QueryStepX() { return stepX; }
  int QueryStepY() { return stepX; }
  ControlType QueryControlType() { return (ControlType)controlType; }
  int QueryLeftKey() { return leftKey; }
  int QueryRightKey() { return rightKey; }
  int QueryUpKey() { return upKey; }
  int QueryDownKey() { return downKey; }
  int QueryRefreshRate() { return refreshRate; }
  int QuerySaveConfig() { return saveConfig; }

  void SetCellWidth(int _val) { cellWidth = _val; }
  void SetVisWidth(int _val) { visWidth = _val; }
  void SetCentreXoff(int _val) { centreXoff = _val; }
  void SetStepX(int _val) { stepX = _val; }
  void SetControlType(ControlType _val) { controlType = (int)_val; }
  void SetLeftKey(int _val) { leftKey = _val; }
  void SetRightKey(int _val) { rightKey = _val; }
  void SetUpKey(int _val) { upKey = _val; }
  void SetDownKey(int _val) { downKey = _val; }
  void SetRefreshRate(int _val) { refreshRate = _val; }
  void SetSaveConfig(int _val) { saveConfig = _val; }
  void StoreInt(char* _key, int _val);
  void LoadInt(char* _key, int& _val);
  void LoadScoreItem(int _num, ScoreItem* _dest);
  void SaveScoreItem(int _num, ScoreItem* _src);

private:

  int cellWidth;
  int visWidth;
  int centreXoff;
  int stepX;
  int controlType;
  int leftKey;
  int rightKey;
  int upKey;
  int downKey;
  int refreshRate;
  int saveConfig;
};



#endif
