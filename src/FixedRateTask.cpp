#include "FixedRateTask.h"

FixedRateTask::FixedRateTask(Executor& executor, Runnable& command, unsigned long period, TimeUnit unit)
    : DelayedTask(executor, command, period, unit) {
}

void FixedRateTask::run() {
  unsigned long int t = currentTimeInUnit();

  if (t >= delay && t - delay >= lastRun) {
    lastRun = t;
    command.run();
  }

  executor.execute(*this);
}
