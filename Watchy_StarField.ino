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
};

WatchyStarField watchy(settings);

void setup()
{
  watchy.init();
}

void loop() {}
