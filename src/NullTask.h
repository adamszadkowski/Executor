#pragma once

#include "Runnable.h"

class NullTask : public Runnable {
 private:
  NullTask();

 public:
  NullTask(NullTask const&) = delete;
  void operator=(NullTask const&) = delete;

  void run() override;

  static NullTask& getInstance();
};
