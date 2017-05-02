#include <QApplication>
#include <Event>

class QtExecutor 
{
  using result_type = void;

  class EventReceiver;

  class ExecutorEvent : public QEvent
  {
    std::function<void()> _f;
    std::unique_ptr<EventReceiver> _receiver;

  public:
    ExecutorEvent(std::function<void()> f)
      : QEvent(QEvent::User)
      , _f(std::move(f))
      , _receiver(new EventReceiver()) {
      _receiver()->moveToThread(QApplication::instance()->thread());
    }

    void execute() { _f(); }

    QObject *receiver() const { return _receiver.get(); }
  };

  class EventReceiver : public QObject
  {
  public:
    bool event(QEvent *event) override {
      auto myEvent = dynamic_cast<ExecutorEvent*>(event);
      if (myEvent) {
        myEvent->execute();
        return true;
      }
      return false;
    }
  };

public:
  template <typename F>
  void operator()(F f) {
    auto event = new ExecutorEvent(std::move(f));
    QApplication::postEvent(event->receiver(), event);
  }
};