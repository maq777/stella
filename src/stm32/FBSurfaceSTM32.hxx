#ifndef FBSURFACE_STM32_HXX
#define FBSURFACE_STM32_HXX

#include "bspf.hxx"
#include "FBSurface.hxx"
#include "FrameBufferSTM32.hxx"

class FBSurfaceSTM32 : public FBSurface
{
  public:
    FBSurfaceSTM32(FrameBufferSTM32& buffer, uInt32 width, uInt32 height,
                  const uInt32* data);
    virtual ~FBSurfaceSTM32() { }

    // Most of the surface drawing primitives are implemented in FBSurface;
    void fillRect(uInt32 x, uInt32 y, uInt32 w, uInt32 h, ColorId color) override { }
    void setDirty() override { }

    uInt32 width() const override { return myWidth; }
    uInt32 height() const override { return myHeight; }

    const Common::Rect& srcRect() const override { return mySrcGUIR; }
    const Common::Rect& dstRect() const override { return myDstGUIR; }
    void setSrcPos(uInt32 x, uInt32 y) override { }
    void setSrcSize(uInt32 w, uInt32 h) override { }
    void setDstPos(uInt32 x, uInt32 y) override { }
    void setDstSize(uInt32 w, uInt32 h) override { }
    void setVisible(bool visible) override { }

    void translateCoords(Int32& x, Int32& y) const override { }
    bool render() override;
    void invalidate() override { }
    void free() override { }
    void reload() override { }
    void resize(uInt32 width, uInt32 height) override { }

  protected:
    void applyAttributes(bool immediate) override { }

  private:
    void createSurface(uInt32 width, uInt32 height, const uInt32* data);

    // Following constructors and assignment operators not supported
    FBSurfaceSTM32() = delete;
    FBSurfaceSTM32(const FBSurfaceSTM32&) = delete;
    FBSurfaceSTM32(FBSurfaceSTM32&&) = delete;
    FBSurfaceSTM32& operator=(const FBSurfaceSTM32&) = delete;
    FBSurfaceSTM32& operator=(FBSurfaceSTM32&&) = delete;

  private:
    Common::Rect mySrcGUIR, myDstGUIR;

  private:
    unique_ptr<uInt32[]> myPixelData;

    uInt32 myWidth, myHeight;
};

#endif
