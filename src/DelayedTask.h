#pragma once

#include "Command.h"
#include "Executor.h"
#include "Runnable.h"
#include "TimeUnit.h"

class DelayedTask : public Runnable {
 public:
  DelayedTask(Executor& executor,   //
              Command command,      //
              unsigned long delay,  //
              TimeUnit unit);       //

  void run() override;

 protected:
  unsigned long currentTimeInUnit();

 protected:
  Executor& executor;
  Command command;
  unsigned long delay;
  TimeUnit unit;

  unsigned long lastRun;
};
