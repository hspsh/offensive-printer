/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "Button.h"
#include "RestClient.h"
#include "utils.hpp"
#include <stdio.h>

RestClient client = RestClient("banana.at.hsp.net.pl", 8000);

Button print14DaysButton(14, INPUT);
Button printOwnerButton(13, INPUT);
Button printStealerButton(12, INPUT);


Subject print14Days;
Subject printOwner;
Subject printStealer;

void setup() {
  Serial.begin(9600);
  client.begin("eduram", "zarazcipodam");

  print14DaysButton.onPress([]() { print14Days.produce(); });
  printOwnerButton.onPress([]() { printOwner.produce(); });
  printStealerButton.onPress([]() { printStealer.produce(); });
}

void loop() {
  delay(100);

  print14Days.consume([]() {
    updateTime();
    client.post("/print/53", createQueryString("EXP", expirationDate(14)));
  });

  printOwner.consume([]() {
    client.post("/print/62", createPrintOnlyQueryString());
  });

  printStealer.consume([]() {
    client.post("/print/63", createPrintOnlyQueryString());
  });
}
