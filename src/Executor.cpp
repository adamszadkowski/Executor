#include "Executor.h"

#include "DelayedTask.h"
#include "FixedRateTask.h"

void Executor::loop() {
  Runnable* c = commands.pop();
  c->run();
}

void Executor::execute(Runnable& command) {
  commands.push(&command);
}

class CyclicTask: public Runnable {
public:
  CyclicTask(Executor& executor, Runnable& command)
      : executor(executor), command(command) {
  }

  void run() override {
    command.run();
    executor.execute(*this);
  }

private:
  Executor& executor;
  Runnable& command;
};

void Executor::executeInCycle(Runnable& command) {
  commands.push(new CyclicTask(*this, command));
}

class FirstRun: public Runnable {
public:
  FirstRun(Executor& executor, Runnable& task, Runnable& command)
      : executor(executor), task(task), command(command) {
  }

  void run() override {
    command.run();
    executor.execute(task);
    delete this;
  }

private:
  Executor& executor;
  Runnable& task;
  Runnable& command;
};

void Executor::scheduleAtFixedRate(Runnable& command,
                                   unsigned long initialDelay,
                                   unsigned long period,
                                   TimeUnit unit) {
  FixedRateTask* t = new FixedRateTask(*this, command, period, unit);

  commands.push(new DelayedTask(*this,
                                *new FirstRun(*this, *t, command),
                                initialDelay,
                                unit));
}

void loop() {
  executor.loop();
}

Executor executor;
