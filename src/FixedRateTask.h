#pragma once

#include "DelayedTask.h"
#include "Executor.h"

class FixedRateTask: public DelayedTask {
public:
  FixedRateTask(Executor& executor,
                Runnable& command,
                unsigned long period,
                TimeUnit unit);

  void run() override;
};
