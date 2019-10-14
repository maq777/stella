#include "FBSurfaceSTM32.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
FBSurfaceSTM32::FBSurfaceSTM32(FrameBufferSTM32&,
                                     uInt32 width, uInt32 height, const uInt32* data)
{
  createSurface(width, height, data);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void FBSurfaceSTM32::createSurface(uInt32 width, uInt32 height,
                                      const uInt32* data)
{
  myWidth = width;
  myHeight = height;

  myPixelData = make_unique<uInt32[]>(width * height);

  ////////////////////////////////////////////////////
  // These *must* be set for the parent class
  myPixels = myPixelData.get();
  myPitch = width;
  ////////////////////////////////////////////////////
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool FBSurfaceSTM32::render()
{
  return true;
}
