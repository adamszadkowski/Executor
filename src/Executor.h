#pragma once

#include "Command.h"
#include "LinkedList.h"
#include "Runnable.h"
#include "TimeUnit.h"

class Executor {
 public:
  void loop();

  void execute(Command command);
  void execute(Runnable& command);

  void executeInCycle(Command command);
  void executeInCycle(Runnable& command);

  void executeWithDelay(Command command, unsigned long delay, TimeUnit unit);
  void executeWithDelay(Runnable& command, unsigned long delay, TimeUnit unit);

  void scheduleAtFixedRate(Command command,             //
                           unsigned long initialDelay,  //
                           unsigned long period,        //
                           TimeUnit unit);              //
  void scheduleAtFixedRate(Runnable& command,           //
                           unsigned long initialDelay,  //
                           unsigned long period,        //
                           TimeUnit unit);              //

 private:
  LinkedList<Command> commands;
};

extern Executor executor;
