#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/progress.hpp>
#include <chrono>
#include <thread>

#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>

class SmallFarm : public nana::form
{
public:
  SmallFarm()
    : _startBtn(*this, "Start", true)
    , _cancelBtn(*this, "Cancel", true)
    , _progressBar(*this, nana::rectangle(10, 40, 280, 20))
  {
    nana::place layout(*this);
    layout.div("vert <><<><button_start><button_cancel><>><><<><progress_bar weight=80><>><>");
    layout["button_start"] << _startBtn;
    layout["button_cancel"] << _cancelBtn;
    layout["progress_bar"] << _progressBar;
    layout.collocate();

    _startBtn.events().click([this]() { start(); });
    _cancelBtn.events().click([this]() { cancel(); });
  }


private:
  void start() {
    _startBtn.enabled(false);
    _storage = stlab::async(stlab::default_executor, [this] {
      _progressBar.amount(50);
      for (int i = 0; i < 50 && !_stop; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        _progressBar.value(i + 1);
      }
      _startBtn.enabled(true);
      _stop = false;
    });
  }

  void cancel() {
    _stop = true;
    _storage = stlab::future<void>();
  }


  std::atomic_bool _stop{ false };
  nana::button    _startBtn;
  nana::button    _cancelBtn;
  nana::progress  _progressBar;
  stlab::future<void> _storage;
};


int main()
{
  SmallFarm ex;
  ex.show();
  nana::exec();
  return 0;
}