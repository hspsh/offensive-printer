#include "Arduino.h"

char *createQueryString(const char *variableName,
                        const char *escapedStringForQuery);

const char *createPrintOnlyQueryString();

char *expirationDate(unsigned int daysToAdd);

void updateTime();

class Subject {
  int times = 0;

public:
  void produce();

  void consume(const std::function<void()> &callback);
};
