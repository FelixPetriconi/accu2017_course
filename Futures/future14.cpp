#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
#include <QLineEdit>
#include "QtScheduler.h"

int main() {
  QLineEdit theAnswerEdit;
  
  auto answer = 
    stlab::async(stlab::default_executor, []{ return 42; } );
  
  stlab::future<void> done = answer.then(
    QtScheduler(),                       // different scheduler
    [&](int a) { theAnswerEdit.setValue(a); }// here update in main thread
  ); 
  
  while (!done.get_try()) {
    // do something in the meantime
  }
}