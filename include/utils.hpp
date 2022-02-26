#include "Arduino.h"
#include <queue>

char *createQueryString(const char *variableName,
                        const char *escapedStringForQuery);

const char *createPrintOnlyQueryString();

char *expirationDate(unsigned int daysToAdd);

void updateTime();

template <int size, class type> class RingBuffer {
  int currentPointer = 0;
  int endingPointer = 0;
  type buffer[size];

public:
  bool empty() { return currentPointer == endingPointer; }

  type pop() {
    type temp = buffer[currentPointer];
    currentPointer = inc(currentPointer);
    return temp;
  }

  void push(type element) {
    buffer[endingPointer] = element;
    endingPointer = inc(endingPointer);
  }

  int inc(int pointer) { return (pointer + 1) % size; }
};

template <int size> class Subject {
    RingBuffer<size, const std::function<void()> *> toExecute;

public:
  Subject() {}

  void execute() {
    while (!this->toExecute.empty())
      (*this->toExecute.pop())();
  }

  void enqueue(const std::function<void()> *callback) {
    this->toExecute.push(callback);
  };
};
