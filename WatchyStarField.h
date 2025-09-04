#ifndef WATCHY_STAR_FIELD_H
#define WATCHY_STAR_FIELD_H
#include <Watchy.h>

class WatchyStarField : public Watchy
{
  using Watchy::Watchy;

public:
  void drawWatchFace();
  void drawTime();
  void drawDate();
  void drawSteps();
  void drawBattery();
  void drawField();
  void drawMoon();

  void drawSun();
  void handleButtonPress() override;
};

#endif
