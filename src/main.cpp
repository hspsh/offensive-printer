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

Subject<10> tasks;

std::function<void()> printExpirationDate = []() {
  updateTime();
  client.post("/print/53", createQueryString("EXP", expirationDate(14)));
};

std::function<void()> printOwnerSticker = []() {
  client.post("/print/62", createPrintOnlyQueryString());
};

std::function<void()> printStealerSticker = []() {
  client.post("/print/63", createPrintOnlyQueryString());
};

void setup() {
  Serial.begin(9600);
  client.begin("eduram", "zarazcipodam");
  updateTime();

  print14DaysButton.onPress([]() { tasks.enqueue(&printExpirationDate); });
  printOwnerButton.onPress([]() { tasks.enqueue(&printOwnerSticker); });
  printStealerButton.onPress([]() { tasks.enqueue(&printStealerSticker); });
}

void loop() {
  delay(100);

  tasks.execute();
}
