#ifndef WATCHY_STAR_FIELD_H
#define WATCHY_STAR_FIELD_H

#ifndef WATCHY_SIM
#include <Watchy.h>
#endif

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
