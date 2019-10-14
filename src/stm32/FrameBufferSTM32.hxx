#ifndef FRAMEBUFFER_STM32_HXX
#define FRAMEBUFFER_STM32_HXX

class OSystem;
class FBSurfaceSTM32;

#include "bspf.hxx"
#include "FrameBuffer.hxx"

class FrameBufferSTM32 : public FrameBuffer
{
  friend class FBSurfaceSTM32;

  public:
    /**
      Creates a new STM32 framebuffer
    */
    explicit FrameBufferSTM32(OSystem& osystem);
    virtual ~FrameBufferSTM32() { }

    //////////////////////////////////////////////////////////////////////
    // The following are derived from public methods in FrameBuffer.hxx
    //////////////////////////////////////////////////////////////////////

    /**
      Updates window title.

      @param title  The title of the application / window
    */
    void setTitle(const string& title) override { }

    /**
      Shows or hides the cursor based on the given boolean value.
    */
    void showCursor(bool show) override { }

    /**
      Answers if the display is currently in fullscreen mode.
    */
    bool fullScreen() const override { return true; }

    /**
      This method is called to retrieve the R/G/B data from the given pixel.

      @param pixel  The pixel containing R/G/B data
      @param r      The red component of the color
      @param g      The green component of the color
      @param b      The blue component of the color
    */
    inline void getRGB(uInt32 pixel, uInt8* r, uInt8* g, uInt8* b) const override { }

    /**
      This method is called to map a given R/G/B triple to the screen palette.

      @param r  The red component of the color.
      @param g  The green component of the color.
      @param b  The blue component of the color.
    */
    inline uInt32 mapRGB(uInt8 r, uInt8 g, uInt8 b) const override { return (r << 16) | (g << 8) | b; }

    /**
      This method is called to get a copy of the specified ARGB data from the
      viewable FrameBuffer area.  Note that this isn't the same as any
      internal surfaces that may be in use; it should return the actual data
      as it is currently seen onscreen.

      @param buffer  A copy of the pixel data in ARGB8888 format
      @param pitch   The pitch (in bytes) for the pixel data
      @param rect    The bounding rectangle for the buffer
    */
    void readPixels(uInt8* buffer, uInt32 pitch, const Common::Rect& rect) const override { }

    /**
      Clear the frame buffer
    */
    void clear() override { }

  protected:
    //////////////////////////////////////////////////////////////////////
    // The following are derived from protected methods in FrameBuffer.hxx
    //////////////////////////////////////////////////////////////////////
    /**
      This method is called to query and initialize the video hardware
      for desktop and fullscreen resolution information.  Since several
      monitors may be attached, we need the resolution for all of them.

      @param fullscreenRes  Maximum resolution supported in fullscreen mode
      @param windowedRes    Maximum resolution supported in windowed mode
      @param renderers      List of renderer names (internal name -> end-user name)
    */
    void queryHardware(vector<Common::Size>& fullscreenRes,
                       vector<Common::Size>& windowedRes,
                       VariantList& renderers) override;

    /**
      This method is called to query the video hardware for the index
      of the display the current window is displayed on

      @return  the current display index or a negative value if no
               window is displayed
    */
    Int32 getCurrentDisplayIndex() override { return 0; }

    /**
      This method is called to preserve the last current windowed position.
    */
    void updateWindowedPos() override { }

    /**
      This method is called to change to the given video mode.

      @param title The title for the created window
      @param mode  The video mode to use

      @return  False on any errors, else true
    */
    bool setVideoMode(const string& title, const VideoMode& mode) override { return true; }

    /**
      This method is called to create a surface with the given attributes.

      @param w     The requested width of the new surface.
      @param h     The requested height of the new surface.
      @param data  If non-null, use the given data values as a static surface
    */
    unique_ptr<FBSurface>
        createSurface(uInt32 w, uInt32 h, const uInt32* data) const override;

    /**
      Grabs or ungrabs the mouse based on the given boolean value.
    */
    void grabMouse(bool grab) override { }

    /**
      Set the icon for the main SDL window.
    */
    void setWindowIcon() override { }

    /**
      This method is called to provide information about the FrameBuffer.
    */
    string about() const override { return "Video system: STM32"; }

    /**
      This method must be called after all drawing is done, and indicates
      that the buffers should be pushed to the physical screen.
    */
    void renderToScreen() override { }

  public:
    /**
      Returns a pointer to the output rendering buffer
    */
    uInt32* getRenderSurface() const { return myRenderSurface; }

  private:
    mutable uInt32* myRenderSurface;

  private:
    // Following constructors and assignment operators not supported
    FrameBufferSTM32() = delete;
    FrameBufferSTM32(const FrameBufferSTM32&) = delete;
    FrameBufferSTM32(FrameBufferSTM32&&) = delete;
    FrameBufferSTM32& operator=(const FrameBufferSTM32&) = delete;
    FrameBufferSTM32& operator=(FrameBufferSTM32&&) = delete;
};

#endif
