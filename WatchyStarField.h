#ifndef WATCHY_STAR_FIELD_H
#define WATCHY_STAR_FIELD_H

#ifndef WATCHY_SIM
#include <Watchy.h>
#endif

typedef void (*OnConnectionCallback)(bool state);
typedef void (*OnNotificationCallback)(Notification notification);

class WatchyStarField : public Watchy
{
  using Watchy::Watchy;

public:
  WatchyStarField(const watchySettings &s) : Watchy(s), app("Watchy") {};
  void initBle(OnConnectionCallback onConnectionCallback, OnNotificationCallback onNotificationCallback);
  void drawWatchFace();
  void drawTime();
  void drawDate();
  void drawSteps();
  void drawBattery();
  void drawField();
  void drawMoon();
  void drawSun();
  void handleButtonPress() override;
  void showAbout() override;
  void tick();

private:
  ChronosESP32 app;
};

#endif
