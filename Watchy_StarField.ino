#include <Watchy.h>
#include <ChronosESP32.h>

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
ChronosESP32 app("Watchy");

void connectionCallback(bool state)
{
  // bool connected = watch.isConnected();
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
  watchy.init();
  app.setConnectionCallback(connectionCallback);
  app.setNotificationCallback(notificationCallback);

  app.begin(); // initializes the BLE
  // make sure the ESP32 is not paired with your phone in the bluetooth settings
  // go to Chronos app > Watches tab > Watches button > Pair New Devices > Search > Select your board
  // you only need to do it once. To disconnect, click on the rotating icon (Top Right)

  // Serial.println(app.getAddress()); // mac address, call after begin()

  app.setBattery(80); // set the battery level, will be synced to the app

  // app.clearNotifications(); // clear the default notification (Chronos app install text)

  app.set24Hour(true); // the 24 hour mode will be overwritten when the command is received from the app
  // this modifies the return of the functions below
  app.getAmPmC(true); // 12 hour mode true->(am/pm), false->(AM/PM), if 24 hour mode returns empty string ("")
  app.getHourC();     // (0-12), (0-23)
  app.getHourZ();     // zero padded hour (00-12), (00-23)
  app.is24Hour();     // returns whether in 24 hour mode
}

void loop()
{
  app.loop();
}
