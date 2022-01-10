/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "Button.h"
#include "ESPPerfectTime.h"
#include "RestClient.h"
#include "TZ.h"
#include <ctime>
#include <stdio.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#define BUTTON_EXTERNAL 5

Button printer(BUTTON_EXTERNAL, INPUT);
RestClient client = RestClient("banana.at.hsp.net.pl", 8000);
uint8_t times = 0;

void updateTime() { pftime::configTime(TZ_Europe_Warsaw, "0.pl.pool.ntp.org"); }

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

char *createQueryString(const char *variableName,
                        const char *escapedStringForQuery) {
  const uint8 SIZE = 100;
  static char queryString[SIZE];

  snprintf((char *)queryString, SIZE, "%s=%s&print=Print", variableName,
           escapedStringForQuery);

  return (char *)&queryString;
}

void setup() {
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  client.begin("eduram", "zarazcipodam");

  printer.onHold([]() { times++; });
}

void loop() {
  delay(100);
  if (times > 0) {
    updateTime();
    int status =
        client.post("/print/53", createQueryString("EXP", expirationDate(14)));
    Serial.println(status);
    times--;
  }
}
