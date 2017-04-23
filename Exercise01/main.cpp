#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/progress.hpp>
#include <chrono>
#include <thread>

class SmallWindow : public nana::form
{
public:
  SmallWindow()
    : _oneBtn(*this, "Start", true)
    , _cancelBtn(*this, "Cancel", true)
    , _progressBar(*this, nana::rectangle(10, 40, 280, 20))
  {
    nana::place layout(*this);
    layout.div("vert <><<><button_start><button_cancel><>><><<><progress_bar weight=80><>><>");
    layout["button_start"] << _oneBtn;
    layout["button_cancel"] << _cancelBtn;
    layout["progress_bar"] << _progressBar;
    layout.collocate();

    _oneBtn.events().click([this]() { start(); });
    _cancelBtn.events().click([this]() { cancel(); });
  }


private:
  void start() {
    _oneBtn.enabled(false);
    _progressBar.amount(50);
    for (int i = 0; i < 50 && !_stop; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      _progressBar.value(i + 1);
    }
    _oneBtn.enabled(true);
  }

  void cancel() {
    _stop = true;
  }

  bool _stop = false;
  nana::button    _oneBtn;
  nana::button    _cancelBtn;
  nana::progress  _progressBar;
};


int main()
{
  SmallWindow ex;
  ex.show();
  nana::exec();
  return 0;
}