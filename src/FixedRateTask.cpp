#include "FixedRateTask.h"

FixedRateTask::FixedRateTask(Executor& executor, Command command, unsigned long period, TimeUnit unit)
    : DelayedTask(executor, command, period, unit) {
}

void FixedRateTask::run() {
  unsigned long int t = currentTimeInUnit();

  if (t >= delay && t - delay >= lastRun) {
    lastRun = t;
    command();
  }

  executor.execute(*this);
}
