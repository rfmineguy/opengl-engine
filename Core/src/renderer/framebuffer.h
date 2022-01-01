#pragma once

namespace Firefly {
struct FrameBufferSpec {
    unsigned int width, height;
    unsigned int samples = 1;
    bool swapChainTarget = false;
};

class FrameBuffer {
public:
    FrameBuffer();
    ~FrameBuffer();

    void Resize(int width, int height);
    void Invalidate();
        void Bind();
        void Unbind();

        unsigned int GetColorAttachment() const { return colorAttachmentId; }
        unsigned int GetWidth() const { return width; }
        unsigned int GetHeight() const { return height; }

    private:
        unsigned int width, height;
        unsigned int samples;

    private:
        unsigned int rendererId = 0;
        unsigned int colorAttachmentId = 0;
        unsigned int depthAttachmentId = 0;

friend class Renderer2D;
};
}
