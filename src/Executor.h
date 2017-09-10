#pragma once

#include "QueueList.h"
#include "TimeUnit.h"
#include "Runnable.h"

class Executor {
public:
  void loop();
  void execute(Runnable& command);
  void executeInCycle(Runnable& command);
  void scheduleAtFixedRate(Runnable& command,
                           unsigned long initialDelay,
                           unsigned long period,
                           TimeUnit unit);

private:
  QueueList<Runnable*> commands;
};

extern Executor executor;
