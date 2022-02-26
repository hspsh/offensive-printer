#include "utils.hpp"
#include "ESPPerfectTime.h"
#include "TZ.h"
#include <ctime>

char *createQueryString(const char *variableName,
                        const char *escapedStringForQuery) {
  const uint8 SIZE = 100;
  static char queryString[SIZE];

  snprintf((char *)queryString, SIZE, "%s=%s&print=Print", variableName,
           escapedStringForQuery);

  return (char *)&queryString;
}

const char *createPrintOnlyQueryString() { return "print=Print"; }

char *expirationDate(unsigned int daysToAdd) {
  const uint8 SIZE = 11;
  static char date[SIZE];

  time_t currentTime;
  time(&currentTime);
  currentTime += daysToAdd * 24 * 3600;

  struct tm *timeinfo;
  timeinfo = localtime(&currentTime);

  strftime((char *)&date, SIZE, "%F", timeinfo);

  return (char *)&date;
}

void updateTime() { pftime::configTime(TZ_Europe_Warsaw, "0.pl.pool.ntp.org"); }
