#ifndef SETTIGNS_H
#define SETTIGNS_H

#define UI_DARKMODE false
#define UI_COLOR_BACKGROUND UI_DARKMODE ? GxEPD_BLACK : GxEPD_WHITE
#define UI_COLOR_FOREGROUND UI_DARKMODE ? GxEPD_WHITE : GxEPD_BLACK

#include "settings.local.h"
#endif
