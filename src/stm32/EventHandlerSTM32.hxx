#ifndef EVENTHANDLER_STM32_HXX
#define EVENTHANDLER_STM32_HXX

#include "EventHandler.hxx"

class EventHandlerSTM32 : public EventHandler
{
  public:
    /**
      Create a new STM32 event handler object
    */
    explicit EventHandlerSTM32(OSystem& osystem);
    virtual ~EventHandlerSTM32();

  private:
    /**
      Enable/disable text events (distinct from single-key events).
    */
    void enableTextEvents(bool enable) override;

    /**
      Collects and dispatches any pending SDL2 events.
    */
    void pollEvent() override;

  private:
    // Following constructors and assignment operators not supported
    EventHandlerSTM32() = delete;
    EventHandlerSTM32(const EventHandlerSTM32&) = delete;
    EventHandlerSTM32(EventHandlerSTM32&&) = delete;
    EventHandlerSTM32& operator=(const EventHandlerSTM32&) = delete;
    EventHandlerSTM32& operator=(EventHandlerSTM32&&) = delete;
};

#endif
