#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <chrono>
#include <thread>
#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>

class cad_report
{
  int   _id;
  std::string _val;

public:
  cad_report() : _id(-1) {}

  cad_report(int id) : _id(id) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    _val = 'A' + id;
  }

  std::string val() const { return _val; }
};


class SmallWindow : public nana::form
{
public:
  SmallWindow()
    : _resetBtn(*this, "Reset", true)
    , _oneBtn(*this, "1", true)
    , _twoBtn(*this, "2", true)
    , _label(*this, "-")
    , _status(*this, "Status: ")
  {
    nana::place layout(*this);
    layout.div("vert <> <<><reset_btn><>> <> <<><button_one><>> <<><button_two><>> <<><label><>> <status>");
    layout["reset_btn"] << _resetBtn;
    layout["button_one"] << _oneBtn;
    layout["button_two"] << _twoBtn;
    layout["label"] << _label;
    layout["status"] << _status;
    layout.collocate();

    _resetBtn.events().click([this]() { reset(); });
    _oneBtn.events().click([this]() { displayReport(0); });
    _twoBtn.events().click([this]() { displayReport(1); });

    _oneBtn.enabled(false);
    _twoBtn.enabled(false);
  }


private:
  void reset() {
    _status.caption("Status: Performing reset ...");
    _reports.clear();
    _requests.clear();

    _reports.push_back(stlab::async(stlab::default_executor, [](int id){
      return cad_report(id);
    }, 0));
    _reports.push_back(stlab::async(stlab::default_executor, [](int id){
      return cad_report(id);
    }, 1));
    _label.caption("-");
    _status.caption("Status: Reset done.");
    _oneBtn.enabled(true);
    _twoBtn.enabled(true);
  }

  void displayReport(int id) {
    if (_reports[id].get_try())
      showReport(_reports[id].get_try().value());
    else
      _requests.push_back(_reports[id].then([_this = this](auto report){ _this->showReport(report);}));
  }

  void showReport(const cad_report& report) {
    _label.caption("Report " + report.val());
  }

  nana::button    _resetBtn;
  nana::button    _oneBtn;
  nana::button    _twoBtn;
  nana::label     _label;
  nana::label     _status;

  std::vector<stlab::future<cad_report>> _reports;
  std::vector<stlab::future<void>> _requests;
};


int main()
{
  SmallWindow ex;
  ex.show();
  nana::exec();
  return 0;
}