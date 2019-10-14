#ifndef OSYSTEM_STM32_HXX
#define OSYSTEM_STM32_HXX

#include "OSystem.hxx"

class OSystemSTM32 : public OSystem
{
  public:
    OSystemSTM32() = default;
    virtual ~OSystemSTM32() = default;

    /**
      Determine the base directory and main configuration file from the
      derived class.  It can also use hints, as described below.

      @param basedir  The base directory for all configuration files
      @param cfgfile  The fully qualified pathname of the config file
                      (including the base directory)
      @param savedir  The default directory to save various other files
      @param loaddir  The default directory to load various other files
      @param useappdir  A hint that the base dir should be set to the
                        app directory; not all ports can do this, so
                        they are free to ignore it
      @param usedir     A hint that the base dir should be set to this
                        parameter; not all ports can do this, so
                        they are free to ignore it
    */
    void getBaseDirAndConfig(string& basedir, string& cfgfile,
              string& savedir, string& loaddir,
              bool useappdir, const string& usedir) override;
};

#endif
