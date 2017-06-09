#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>
#include <iostream>
#include <QLineEdit>
#include "QtScheduler.h"

int main() {
  QLineEdit lineEdit;
  
  auto answer = 
    stlab::async(stlab::default_executor, []{ return 42; } );
  
  stlab::future<void> done = answer.then(
    QtScheduler(),                       // different scheduler
    [&](int a) { lineEdit->setValue(a); }// here update in main thread
  ); 
  
  while (!done.get_try()) {
    // do something in the meantime
  }
}