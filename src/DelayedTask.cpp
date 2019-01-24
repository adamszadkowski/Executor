#include "DelayedTask.h"

#include "Arduino.h"

DelayedTask::DelayedTask(Executor& executor, Command command, unsigned long delay, TimeUnit unit)
    : executor(executor), command(command), delay(delay), unit(unit) {
  lastRun = currentTimeInUnit();
}

void DelayedTask::run() {
  unsigned long int t = currentTimeInUnit();

  if (t >= delay && t - delay >= lastRun) {
    lastRun = t;
    command();
    delete this;
  } else {
    executor.execute(*this);
  }
}

unsigned long DelayedTask::currentTimeInUnit() {
  switch (unit) {
    case MICROSECONDS:
      return micros();
    case MILLISECONDS:
      return millis();
    case SECONDS:
      return millis() / 1000;
    case MINUTES:
      return millis() / (60 * 1000);
    case HOURS:
      return millis() / (60 * 60 * 1000);
    case DAYS:
      return millis() / (24 * 60 * 60 * 1000);
    default:
      return millis();
  }
}
