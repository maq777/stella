#ifndef SETTINGS_STM32_HXX
#define SETTINGS_STM32_HXX

#include "Settings.hxx"

class SettingsSTM32 : public Settings
{
  public:
    /**
      Create a new UNIX settings object
    */
    explicit SettingsSTM32();
    virtual ~SettingsSTM32() = default;

  private:
    // Following constructors and assignment operators not supported
    SettingsSTM32(const SettingsSTM32&) = delete;
    SettingsSTM32(SettingsSTM32&&) = delete;
    SettingsSTM32& operator=(const SettingsSTM32&) = delete;
    SettingsSTM32& operator=(SettingsSTM32&&) = delete;
};

#endif
