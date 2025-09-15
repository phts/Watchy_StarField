#include <ChronosESP32.h>
#include <math.h>
#include "WatchyStarField.h"
#include "settings.h"
#include "Dusk2Dawn.h"
#include "moonPhaser.h"
#include "Seven_Segment10pt7b.h"
#include "DSEG7_Classic_Regular_15.h"
#include "DSEG7_Classic_Bold_25.h"
#include "DSEG7_Classic_Regular_39.h"
#include "icons.h"

RTC_DATA_ATTR bool HOUR_SET = true;

moonPhaser moonP;

void WatchyStarField::handleButtonPress()
{
  if (guiState == WATCHFACE_STATE)
  {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
    if (wakeupBit & DOWN_BTN_MASK)
    {
      RTC.read(currentTime);
      Watchy::vibMotor(300, (currentTime.Hour > (uint8_t)12 ? currentTime.Hour - (uint8_t)12 : currentTime.Hour) * 2);
      delay(700);
      Watchy::vibMotor(200, (currentTime.Minute / (uint8_t)10) * 2 + 1);
      return;
    }
  }
  Watchy::handleButtonPress();
}

void WatchyStarField::drawWatchFace()
{
  display.fillScreen(UI_COLOR_BACKGROUND);
  display.setTextColor(UI_COLOR_FOREGROUND);
  drawField();
  drawTime();
  drawDate();
  drawSteps();
  drawBattery();

  display.drawBitmap(118, 168, WIFI_CONFIGURED ? wifi : wifioff, 25, 18, UI_COLOR_FOREGROUND);
  drawMoon();
  drawSun();
}

void WatchyStarField::drawTime()
{
  display.setFont(&DSEG7_Classic_Bold_53);
  display.setCursor(6, 53 + 5);
  long ss = currentTime.Hour * 60 + currentTime.Minute;
  int sh = ss / 60;

  if (HOUR_SET == false && sh >= 12)
  {
    display.fillRect(7, 60, 25, 9, UI_COLOR_BACKGROUND);
    display.drawBitmap(7, 60, pm, 25, 9, UI_COLOR_FOREGROUND);
  }
  else if (HOUR_SET == false && sh < 12)
  {
    display.fillRect(7, 60, 25, 9, UI_COLOR_BACKGROUND);
    display.drawBitmap(7, 60, am, 25, 9, UI_COLOR_FOREGROUND);
  }

  if (HOUR_SET == false && sh > 12)
  {
    sh -= 12;
  }
  int sm = ss % 60;
  int a = sh >= 10 ? sh / 10 : 0;
  int b = sh % 10;
  int c = sm >= 10 ? sm / 10 : 0;
  int d = sm % 10;

  if (a == 0)
    display.drawBitmap(11, 5, fd_0, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 1)
    display.drawBitmap(11, 5, fd_1, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 2)
    display.drawBitmap(11, 5, fd_2, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 3)
    display.drawBitmap(11, 5, fd_3, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 4)
    display.drawBitmap(11, 5, fd_4, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 5)
    display.drawBitmap(11, 5, fd_5, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 6)
    display.drawBitmap(11, 5, fd_6, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 7)
    display.drawBitmap(11, 5, fd_7, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 8)
    display.drawBitmap(11, 5, fd_8, 33, 53, UI_COLOR_FOREGROUND);
  else if (a == 9)
    display.drawBitmap(11, 5, fd_9, 33, 53, UI_COLOR_FOREGROUND);

  if (b == 0)
    display.drawBitmap(55, 5, fd_0, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 1)
    display.drawBitmap(55, 5, fd_1, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 2)
    display.drawBitmap(55, 5, fd_2, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 3)
    display.drawBitmap(55, 5, fd_3, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 4)
    display.drawBitmap(55, 5, fd_4, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 5)
    display.drawBitmap(55, 5, fd_5, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 6)
    display.drawBitmap(55, 5, fd_6, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 7)
    display.drawBitmap(55, 5, fd_7, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 8)
    display.drawBitmap(55, 5, fd_8, 33, 53, UI_COLOR_FOREGROUND);
  else if (b == 9)
    display.drawBitmap(55, 5, fd_9, 33, 53, UI_COLOR_FOREGROUND);

  if (c == 0)
    display.drawBitmap(111, 5, fd_0, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 1)
    display.drawBitmap(111, 5, fd_1, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 2)
    display.drawBitmap(111, 5, fd_2, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 3)
    display.drawBitmap(111, 5, fd_3, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 4)
    display.drawBitmap(111, 5, fd_4, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 5)
    display.drawBitmap(111, 5, fd_5, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 6)
    display.drawBitmap(111, 5, fd_6, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 7)
    display.drawBitmap(111, 5, fd_7, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 8)
    display.drawBitmap(111, 5, fd_8, 33, 53, UI_COLOR_FOREGROUND);
  else if (c == 9)
    display.drawBitmap(111, 5, fd_9, 33, 53, UI_COLOR_FOREGROUND);

  if (d == 0)
    display.drawBitmap(155, 5, fd_0, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 1)
    display.drawBitmap(155, 5, fd_1, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 2)
    display.drawBitmap(155, 5, fd_2, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 3)
    display.drawBitmap(155, 5, fd_3, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 4)
    display.drawBitmap(155, 5, fd_4, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 5)
    display.drawBitmap(155, 5, fd_5, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 6)
    display.drawBitmap(155, 5, fd_6, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 7)
    display.drawBitmap(155, 5, fd_7, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 8)
    display.drawBitmap(155, 5, fd_8, 33, 53, UI_COLOR_FOREGROUND);
  else if (d == 9)
    display.drawBitmap(155, 5, fd_9, 33, 53, UI_COLOR_FOREGROUND);
}

void WatchyStarField::drawDate()
{
  display.setFont(&Seven_Segment10pt7b);

  int16_t x1, y1;
  uint16_t w, h;

  String dayOfWeek = dayStr(currentTime.Wday);
  dayOfWeek = dayOfWeek.substring(0, 3);
  display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
  display.setCursor(64 - w, 86);
  display.println(dayOfWeek);

  String month = monthShortStr(currentTime.Month);
  display.getTextBounds(month, 60, 110, &x1, &y1, &w, &h);
  display.setCursor(79 - w, 110);
  display.println(month);

  int da = currentTime.Day;
  int ye = currentTime.Year + 1970;

  int a = da / 10;
  int b = da % 10;
  int c = ye / 1000;
  ye = ye % 1000;
  int d = ye / 100;
  ye = ye % 100;
  int e = ye / 10;
  ye = ye % 10;
  int f = ye;

  if (a == 0)
    display.drawBitmap(8, 95, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 1)
    display.drawBitmap(8, 95, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 2)
    display.drawBitmap(8, 95, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 3)
    display.drawBitmap(8, 95, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 4)
    display.drawBitmap(8, 95, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 5)
    display.drawBitmap(8, 95, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 6)
    display.drawBitmap(8, 95, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 7)
    display.drawBitmap(8, 95, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 8)
    display.drawBitmap(8, 95, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 9)
    display.drawBitmap(8, 95, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (b == 0)
    display.drawBitmap(29, 95, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 1)
    display.drawBitmap(29, 95, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 2)
    display.drawBitmap(29, 95, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 3)
    display.drawBitmap(29, 95, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 4)
    display.drawBitmap(29, 95, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 5)
    display.drawBitmap(29, 95, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 6)
    display.drawBitmap(29, 95, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 7)
    display.drawBitmap(29, 95, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 8)
    display.drawBitmap(29, 95, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 9)
    display.drawBitmap(29, 95, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (c == 0)
    display.drawBitmap(8, 129, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 1)
    display.drawBitmap(8, 129, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 2)
    display.drawBitmap(8, 129, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 3)
    display.drawBitmap(8, 129, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 4)
    display.drawBitmap(8, 129, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 5)
    display.drawBitmap(8, 129, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 6)
    display.drawBitmap(8, 129, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 7)
    display.drawBitmap(8, 129, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 8)
    display.drawBitmap(8, 129, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 9)
    display.drawBitmap(8, 129, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (d == 0)
    display.drawBitmap(29, 129, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 1)
    display.drawBitmap(29, 129, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 2)
    display.drawBitmap(29, 129, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 3)
    display.drawBitmap(29, 129, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 4)
    display.drawBitmap(29, 129, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 5)
    display.drawBitmap(29, 129, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 6)
    display.drawBitmap(29, 129, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 7)
    display.drawBitmap(29, 129, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 8)
    display.drawBitmap(29, 129, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 9)
    display.drawBitmap(29, 129, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (e == 0)
    display.drawBitmap(50, 129, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 1)
    display.drawBitmap(50, 129, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 2)
    display.drawBitmap(50, 129, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 3)
    display.drawBitmap(50, 129, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 4)
    display.drawBitmap(50, 129, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 5)
    display.drawBitmap(50, 129, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 6)
    display.drawBitmap(50, 129, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 7)
    display.drawBitmap(50, 129, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 8)
    display.drawBitmap(50, 129, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 9)
    display.drawBitmap(50, 129, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (f == 0)
    display.drawBitmap(71, 129, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 1)
    display.drawBitmap(71, 129, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 2)
    display.drawBitmap(71, 129, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 3)
    display.drawBitmap(71, 129, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 4)
    display.drawBitmap(71, 129, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 5)
    display.drawBitmap(71, 129, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 6)
    display.drawBitmap(71, 129, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 7)
    display.drawBitmap(71, 129, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 8)
    display.drawBitmap(71, 129, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (f == 9)
    display.drawBitmap(71, 129, dd_9, 16, 25, UI_COLOR_FOREGROUND);
}
void WatchyStarField::drawSteps()
{
  // reset step counter at midnight
  if (currentTime.Hour == 0 && currentTime.Minute == 0)
  {
    sensor.resetStepCounter();
  }
  uint32_t stepCount = sensor.getCounter();
  uint32_t l5 = 61 * stepCount / 10000;

  if (l5 > 61)
  {
    l5 = 61;
  }

  display.fillRect(131, 148, l5, 9, UI_COLOR_FOREGROUND);

  int a = stepCount / 10000;
  stepCount = stepCount % 10000;
  int b = stepCount / 1000;
  stepCount = stepCount % 1000;
  int c = stepCount / 100;
  stepCount = stepCount % 100;
  int d = stepCount / 10;
  int e = stepCount % 10;

  if (a == 0)
    display.drawBitmap(8, 165, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 1)
    display.drawBitmap(8, 165, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 2)
    display.drawBitmap(8, 165, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 3)
    display.drawBitmap(8, 165, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 4)
    display.drawBitmap(8, 165, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 5)
    display.drawBitmap(8, 165, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 6)
    display.drawBitmap(8, 165, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 7)
    display.drawBitmap(8, 165, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 8)
    display.drawBitmap(8, 165, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (a == 9)
    display.drawBitmap(8, 165, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (b == 0)
    display.drawBitmap(29, 165, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 1)
    display.drawBitmap(29, 165, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 2)
    display.drawBitmap(29, 165, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 3)
    display.drawBitmap(29, 165, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 4)
    display.drawBitmap(29, 165, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 5)
    display.drawBitmap(29, 165, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 6)
    display.drawBitmap(29, 165, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 7)
    display.drawBitmap(29, 165, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 8)
    display.drawBitmap(29, 165, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (b == 9)
    display.drawBitmap(29, 165, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (c == 0)
    display.drawBitmap(50, 165, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 1)
    display.drawBitmap(50, 165, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 2)
    display.drawBitmap(50, 165, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 3)
    display.drawBitmap(50, 165, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 4)
    display.drawBitmap(50, 165, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 5)
    display.drawBitmap(50, 165, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 6)
    display.drawBitmap(50, 165, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 7)
    display.drawBitmap(50, 165, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 8)
    display.drawBitmap(50, 165, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (c == 9)
    display.drawBitmap(50, 165, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (d == 0)
    display.drawBitmap(71, 165, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 1)
    display.drawBitmap(71, 165, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 2)
    display.drawBitmap(71, 165, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 3)
    display.drawBitmap(71, 165, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 4)
    display.drawBitmap(71, 165, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 5)
    display.drawBitmap(71, 165, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 6)
    display.drawBitmap(71, 165, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 7)
    display.drawBitmap(71, 165, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 8)
    display.drawBitmap(71, 165, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (d == 9)
    display.drawBitmap(71, 165, dd_9, 16, 25, UI_COLOR_FOREGROUND);

  if (e == 0)
    display.drawBitmap(92, 165, dd_0, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 1)
    display.drawBitmap(92, 165, dd_1, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 2)
    display.drawBitmap(92, 165, dd_2, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 3)
    display.drawBitmap(92, 165, dd_3, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 4)
    display.drawBitmap(92, 165, dd_4, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 5)
    display.drawBitmap(92, 165, dd_5, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 6)
    display.drawBitmap(92, 165, dd_6, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 7)
    display.drawBitmap(92, 165, dd_7, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 8)
    display.drawBitmap(92, 165, dd_8, 16, 25, UI_COLOR_FOREGROUND);
  else if (e == 9)
    display.drawBitmap(92, 165, dd_9, 16, 25, UI_COLOR_FOREGROUND);
}
void WatchyStarField::drawBattery()
{
  int8_t batteryLevel = 0;
  float VBAT = getBatteryVoltage();

  if (VBAT > 4.0)
  {
    batteryLevel = 37;
  }
  else if (VBAT > 3.9 && VBAT <= 4.0)
  {
    batteryLevel = 33;
  }
  else if (VBAT > 3.7 && VBAT <= 3.9)
  {
    batteryLevel = 28;
  }
  else if (VBAT > 3.6 && VBAT <= 3.7)
  {
    batteryLevel = 23;
  }
  else if (VBAT > 3.5 && VBAT <= 3.6)
  {
    batteryLevel = 18;
  }
  else if (VBAT > 3.4 && VBAT <= 3.5)
  {
    batteryLevel = 13;
  }
  else if (VBAT > 3.3 && VBAT <= 3.4)
  {
    batteryLevel = 8;
  }
  else if (VBAT > 3.2 && VBAT <= 3.3)
  {
    batteryLevel = 4;
  }
  else if (VBAT <= 3.2)
  {
    batteryLevel = 0;
  }

  display.fillRect(155, 169, batteryLevel, 15, UI_COLOR_FOREGROUND);
}

void WatchyStarField::drawField()
{
  display.drawBitmap(0, 0, field, 200, 200, UI_COLOR_FOREGROUND);
}

void WatchyStarField::drawMoon()
{
  moonData_t moon; // variable to receive the data

  // January 31st, 2020 @ 1:30PM UTC
  int year = currentTime.Year + 1970;
  int32_t month = currentTime.Month;
  int32_t day = currentTime.Day;
  double hour = currentTime.Hour + 0.1;

  moon = moonP.getPhase(year, month, day, hour);

  int ag = moon.angle;
  double lt = moon.percentLit;

  // Waxing: 0-180
  // Waning: 180-360

  display.drawBitmap(130, 73, luna_bg, 64, 64, GxEPD_BLACK);
  if (ag <= 180)
  {
    if (lt < 0.1)
      display.drawBitmap(131, 74, luna1, 61, 61, GxEPD_WHITE);
    else if (lt < 0.25)
      display.drawBitmap(131, 74, luna12, 61, 61, GxEPD_WHITE);
    else if (lt < 0.4)
      display.drawBitmap(131, 74, luna11, 61, 61, GxEPD_WHITE);
    else if (lt < 0.6)
      display.drawBitmap(131, 74, luna10, 61, 61, GxEPD_WHITE);
    else if (lt < 0.75)
      display.drawBitmap(131, 74, luna9, 61, 61, GxEPD_WHITE);
    else if (lt < 0.9)
      display.drawBitmap(131, 74, luna8, 61, 61, GxEPD_WHITE);
    else
      display.drawBitmap(131, 74, luna7, 61, 61, GxEPD_WHITE);
  }
  else
  {
    if (lt < 0.1)
      display.drawBitmap(131, 74, luna1, 61, 61, GxEPD_WHITE);
    else if (lt < 0.25)
      display.drawBitmap(131, 74, luna2, 61, 61, GxEPD_WHITE);
    else if (lt < 0.4)
      display.drawBitmap(131, 74, luna3, 61, 61, GxEPD_WHITE);
    else if (lt < 0.6)
      display.drawBitmap(131, 74, luna4, 61, 61, GxEPD_WHITE);
    else if (lt < 0.75)
      display.drawBitmap(131, 74, luna5, 61, 61, GxEPD_WHITE);
    else if (lt < 0.9)
      display.drawBitmap(131, 74, luna6, 61, 61, GxEPD_WHITE);
    else
      display.drawBitmap(131, 74, luna7, 61, 61, GxEPD_WHITE);
  }
}

void WatchyStarField::drawSun()
{
  Dusk2Dawn location(SETTINGS_LOCATION, SETTINGS_TIMEZONE);
  int year = currentTime.Year + 1970;
  int32_t month = currentTime.Month;
  int32_t day = currentTime.Day;
  int sr = location.sunrise(year, month, day, false);
  int ss = location.sunset(year, month, day, false);

  long k = currentTime.Hour * 60 + currentTime.Minute;
  int tk = (k - sr) * 60 / (ss - sr);
  if (k > ss)
    tk = 60;
  else if (k < sr)
    tk = 0;
  display.drawBitmap(110, 132 - tk, arr, 3, 5, UI_COLOR_FOREGROUND);

  int rh = sr / 60;
  int rm = sr % 60;
  int sh = ss / 60;
  int sm = ss % 60;

  if (HOUR_SET == false && rh > 12)
  {
    rh -= 12;
  }

  if (HOUR_SET == false && sh > 12)
  {
    sh -= 12;
  }

  int a = sh >= 10 ? sh / 10 : 0;
  int b = sh % 10;
  int c = sm >= 10 ? sm / 10 : 0;
  int d = sm % 10;
  int e = rh >= 10 ? rh / 10 : 0;
  int f = rh % 10;
  int g = rm >= 10 ? rm / 10 : 0;
  int h = rm % 10;

  if (a == 0)
    display.drawBitmap(116, 67, num_0, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 1)
    display.drawBitmap(116, 67, num_1, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 2)
    display.drawBitmap(116, 67, num_2, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 3)
    display.drawBitmap(116, 67, num_3, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 4)
    display.drawBitmap(116, 67, num_4, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 5)
    display.drawBitmap(116, 67, num_5, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 6)
    display.drawBitmap(116, 67, num_6, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 7)
    display.drawBitmap(116, 67, num_7, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 8)
    display.drawBitmap(116, 67, num_8, 3, 5, UI_COLOR_FOREGROUND);
  else if (a == 9)
    display.drawBitmap(116, 67, num_9, 3, 5, UI_COLOR_FOREGROUND);

  if (b == 0)
    display.drawBitmap(120, 67, num_0, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 1)
    display.drawBitmap(120, 67, num_1, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 2)
    display.drawBitmap(120, 67, num_2, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 3)
    display.drawBitmap(120, 67, num_3, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 4)
    display.drawBitmap(120, 67, num_4, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 5)
    display.drawBitmap(120, 67, num_5, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 6)
    display.drawBitmap(120, 67, num_6, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 7)
    display.drawBitmap(120, 67, num_7, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 8)
    display.drawBitmap(120, 67, num_8, 3, 5, UI_COLOR_FOREGROUND);
  else if (b == 9)
    display.drawBitmap(120, 67, num_9, 3, 5, UI_COLOR_FOREGROUND);

  if (c == 0)
    display.drawBitmap(128, 67, num_0, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 1)
    display.drawBitmap(128, 67, num_1, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 2)
    display.drawBitmap(128, 67, num_2, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 3)
    display.drawBitmap(128, 67, num_3, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 4)
    display.drawBitmap(128, 67, num_4, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 5)
    display.drawBitmap(128, 67, num_5, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 6)
    display.drawBitmap(128, 67, num_6, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 7)
    display.drawBitmap(128, 67, num_7, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 8)
    display.drawBitmap(128, 67, num_8, 3, 5, UI_COLOR_FOREGROUND);
  else if (c == 9)
    display.drawBitmap(128, 67, num_9, 3, 5, UI_COLOR_FOREGROUND);

  if (d == 0)
    display.drawBitmap(132, 67, num_0, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 1)
    display.drawBitmap(132, 67, num_1, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 2)
    display.drawBitmap(132, 67, num_2, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 3)
    display.drawBitmap(132, 67, num_3, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 4)
    display.drawBitmap(132, 67, num_4, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 5)
    display.drawBitmap(132, 67, num_5, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 6)
    display.drawBitmap(132, 67, num_6, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 7)
    display.drawBitmap(132, 67, num_7, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 8)
    display.drawBitmap(132, 67, num_8, 3, 5, UI_COLOR_FOREGROUND);
  else if (d == 9)
    display.drawBitmap(132, 67, num_9, 3, 5, UI_COLOR_FOREGROUND);

  if (e == 0)
    display.drawBitmap(116, 137, num_0, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 1)
    display.drawBitmap(116, 137, num_1, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 2)
    display.drawBitmap(116, 137, num_2, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 3)
    display.drawBitmap(116, 137, num_3, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 4)
    display.drawBitmap(116, 137, num_4, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 5)
    display.drawBitmap(116, 137, num_5, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 6)
    display.drawBitmap(116, 137, num_6, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 7)
    display.drawBitmap(116, 137, num_7, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 8)
    display.drawBitmap(116, 137, num_8, 3, 5, UI_COLOR_FOREGROUND);
  else if (e == 9)
    display.drawBitmap(116, 137, num_9, 3, 5, UI_COLOR_FOREGROUND);

  if (f == 0)
    display.drawBitmap(120, 137, num_0, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 1)
    display.drawBitmap(120, 137, num_1, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 2)
    display.drawBitmap(120, 137, num_2, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 3)
    display.drawBitmap(120, 137, num_3, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 4)
    display.drawBitmap(120, 137, num_4, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 5)
    display.drawBitmap(120, 137, num_5, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 6)
    display.drawBitmap(120, 137, num_6, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 7)
    display.drawBitmap(120, 137, num_7, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 8)
    display.drawBitmap(120, 137, num_8, 3, 5, UI_COLOR_FOREGROUND);
  else if (f == 9)
    display.drawBitmap(120, 137, num_9, 3, 5, UI_COLOR_FOREGROUND);

  if (g == 0)
    display.drawBitmap(128, 137, num_0, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 1)
    display.drawBitmap(128, 137, num_1, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 2)
    display.drawBitmap(128, 137, num_2, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 3)
    display.drawBitmap(128, 137, num_3, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 4)
    display.drawBitmap(128, 137, num_4, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 5)
    display.drawBitmap(128, 137, num_5, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 6)
    display.drawBitmap(128, 137, num_6, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 7)
    display.drawBitmap(128, 137, num_7, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 8)
    display.drawBitmap(128, 137, num_8, 3, 5, UI_COLOR_FOREGROUND);
  else if (g == 9)
    display.drawBitmap(128, 137, num_9, 3, 5, UI_COLOR_FOREGROUND);

  if (h == 0)
    display.drawBitmap(132, 137, num_0, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 1)
    display.drawBitmap(132, 137, num_1, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 2)
    display.drawBitmap(132, 137, num_2, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 3)
    display.drawBitmap(132, 137, num_3, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 4)
    display.drawBitmap(132, 137, num_4, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 5)
    display.drawBitmap(132, 137, num_5, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 6)
    display.drawBitmap(132, 137, num_6, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 7)
    display.drawBitmap(132, 137, num_7, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 8)
    display.drawBitmap(132, 137, num_8, 3, 5, UI_COLOR_FOREGROUND);
  else if (h == 9)
    display.drawBitmap(132, 137, num_9, 3, 5, UI_COLOR_FOREGROUND);
}

void WatchyStarField::initBle()
{
  // chronos.setConnectionCallback(onConnectionCallback);
  // chronos.setNotificationCallback(onNotificationCallback);
  _bleMacAddress = "none";

  chronos.begin(); // initializes the BLE
  // make sure the ESP32 is not paired with your phone in the bluetooth settings
  // go to Chronos app > Watches tab > Watches button > Pair New Devices > Search > Select your board
  // you only need to do it once. To disconnect, click on the rotating icon (Top Right)

  _bleMacAddress = chronos.getAddress();
  // Serial.println(_bleMacAddress);

  // chronos.setBattery(80); // set the battery level, will be synced to the app

  // chronos.clearNotifications(); // clear the default notification (Chronos app install text)

  // chronos.set24Hour(true); // the 24 hour mode will be overwritten when the command is received from the app
  // this modifies the return of the functions below
  // chronos.getAmPmC(true); // 12 hour mode true->(am/pm), false->(AM/PM), if 24 hour mode returns empty string ("")
  // chronos.getHourC();     // (0-12), (0-23)
  // chronos.getHourZ();     // zero padded hour (00-12), (00-23)
  // chronos.is24Hour();     // returns whether in 24 hour mode
}

void WatchyStarField::showAbout()
{
  Watchy::showAbout();
  display.print("ble mac: ");
  display.println(_bleMacAddress);
  display.display(true);
}

void WatchyStarField::tick()
{
  chronos.loop();
}
