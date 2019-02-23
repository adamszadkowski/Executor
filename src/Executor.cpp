#include "Executor.h"

#include "DelayedTask.h"
#include "FixedRateTask.h"

void Executor::loop() {
  Command c = commands.shift();
  c();
}

void Executor::execute(Command command) {
  commands.add(command);
}

void Executor::execute(Runnable& command) {
  commands.add([&command]() { command.run(); });
}

void Executor::executeInCycle(Command command) {
  execute([command, this]() {
    command();
    executeInCycle(command);
  });
}

void Executor::executeInCycle(Runnable& command) {
  executeInCycle([&command]() { command.run(); });
}

void Executor::executeWithDelay(Command command, unsigned long initialDelay, TimeUnit unit) {
  execute(*new DelayedTask(*this, command, initialDelay, unit));
}

void Executor::executeWithDelay(Runnable& command, unsigned long initialDelay, TimeUnit unit) {
  executeWithDelay([&command]() { command.run(); }, initialDelay, unit);
}

void Executor::scheduleAtFixedRate(Command command, unsigned long initialDelay, unsigned long period, TimeUnit unit) {
  execute(*new DelayedTask(*this,
                           [command, period, unit, this]() {
                             command();
                             execute(*new FixedRateTask(*this, command, period, unit));
                           },
                           initialDelay, unit));
}

void Executor::scheduleAtFixedRate(Runnable& command, unsigned long initialDelay, unsigned long period, TimeUnit unit) {
  scheduleAtFixedRate([&command]() { command.run(); }, initialDelay, period, unit);
}

extern "C" {
void loop() {
  executor.loop();
}
}

Executor executor;
