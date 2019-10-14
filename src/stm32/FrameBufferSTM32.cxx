#include "bspf.hxx"

#include "OSystem.hxx"
#include "AtariNTSC.hxx"
#include "TIAConstants.hxx"

#include "FBSurfaceSTM32.hxx"
#include "FrameBufferSTM32.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
FrameBufferSTM32::FrameBufferSTM32(OSystem& osystem)
  : FrameBuffer(osystem),
    myRenderSurface(nullptr)
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void FrameBufferSTM32::queryHardware(vector<Common::Size>& fullscreenRes,
                                        vector<Common::Size>& windowedRes,
                                        VariantList& renderers)
{
  fullscreenRes.emplace_back(1920, 1080);
  windowedRes.emplace_back(1920, 1080);

  VarList::push_back(renderers, "software", "Software");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
unique_ptr<FBSurface>
    FrameBufferSTM32::createSurface(uInt32 w, uInt32 h, const uInt32* data) const
{
  unique_ptr<FBSurface> ptr = make_unique<FBSurfaceSTM32>
      (const_cast<FrameBufferSTM32&>(*this), w, h, data);

  if(w == AtariNTSC::outWidth(TIAConstants::frameBufferWidth) &&
     h == TIAConstants::frameBufferHeight)
  {
    uInt32 pitch;
    ptr.get()->basePtr(myRenderSurface, pitch);
  }

  return ptr;
}
