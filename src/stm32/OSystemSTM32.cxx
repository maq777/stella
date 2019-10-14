#include "FSNode.hxx"
#include "OSystemSTM32.hxx"

#ifdef _WIN32
  const string slash = "\\";
#else
  const string slash = "/";
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystemSTM32::getBaseDirAndConfig(string& basedir, string& cfgfile,
        string& savedir, string& loaddir,
        bool useappdir, const string& usedir)
{
  loaddir = savedir = basedir = "." + slash;
}
