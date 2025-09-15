#include <ChronosESP32.h>
#include <Watchy.h>

#include "settings.h"
#include "WatchyStarField.h"

watchySettings settings{
    .cityID = "",
    .lat = "",
    .lon = "",
    .weatherAPIKey = "",
    .weatherURL = "",
    .weatherUnit = "",
    .weatherLang = "",
    .weatherUpdateInterval = 0,
    .ntpServer = "pool.ntp.org",
    .gmtOffset = 3600 * SETTINGS_TIMEZONE,
    .vibrateOClock = SETTINGS_VIBRATE_O_CLOCK,
    .lightUI = true,
};

WatchyStarField watchy(settings);

void connectionCallback(bool state)
{
  watchy.vibMotor(50, 8);
}

void notificationCallback(Notification notification)
{
  // Serial.print("Notification received at ");
  // Serial.println(notification.time);
  // Serial.print("From: ");
  // Serial.print(notification.app);
  // Serial.print("\tIcon: ");
  // Serial.println(notification.icon);
  // Serial.println(notification.title);
  // Serial.println(notification.message);
  // see loop on how to access notifications
  watchy.vibMotor(100, 4);
}

void setup()
{
  // Serial.begin(9600);
  // Serial.println("begin");
  watchy.init();
  watchy.initBle();
}

void loop()
{
  watchy.tick();
}
