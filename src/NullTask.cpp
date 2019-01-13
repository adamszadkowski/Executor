#include "NullTask.h"

NullTask::NullTask() {}

void NullTask::run() {}

NullTask& NullTask::getInstance() {
  static NullTask instance;
  return instance;
}
