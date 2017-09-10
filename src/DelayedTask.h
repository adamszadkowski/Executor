#pragma once

#include "Runnable.h"
#include "Executor.h"
#include "TimeUnit.h"

class DelayedTask: public Runnable {
public:
  DelayedTask(Executor& executor,
              Runnable& command,
              unsigned long delay,
              TimeUnit unit);

  void run() override;

protected:
  unsigned long currentTimeInUnit();

protected:
  Executor& executor;
  Runnable& command;
  unsigned long delay;
  TimeUnit unit;

  unsigned long lastRun;
};
