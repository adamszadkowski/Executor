#pragma once

#include "Command.h"
#include "DelayedTask.h"
#include "Executor.h"

class FixedRateTask : public DelayedTask {
 public:
  FixedRateTask(Executor& executor,    //
                Command command,       //
                unsigned long period,  //
                TimeUnit unit);        //

  void run() override;
};
