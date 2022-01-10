/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "Button.h"
#include "RestClient.h"
#include <time.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#define BUTTON_EXTERNAL 5

Button printer(BUTTON_EXTERNAL, INPUT);
RestClient client = RestClient("banana.at.hsp.net.pl", 8000);
bool flag = false;

void setup() {
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  client.begin("eduram", "zarazcipodam");

  printer.onHold([]() { flag = true; });
}

void loop() {
  delay(100);
  if (flag) {
    int status = client.post("/print/46", "LINE2=XOX&LINE1=OXO&print=Print");
    Serial.println(status);
    flag = false;
  }
}
