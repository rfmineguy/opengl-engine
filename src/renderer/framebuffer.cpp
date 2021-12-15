#include "../corepch.h"
#include "framebuffer.h"
#include <glad/glad.h>

namespace Firefly {
FrameBuffer::FrameBuffer() 
{
}

FrameBuffer::~FrameBuffer() {
    glDeleteTextures(1, &colorAttachmentId);
    glDeleteTextures(1, &depthAttachmentId);
    glDeleteFramebuffers(1, &rendererId);
}

void FrameBuffer::Resize(int width, int height) {
    this->width = width;
    this->height = height;
    Invalidate();
}

void FrameBuffer::Invalidate() {
    if (rendererId) {
        glDeleteFramebuffers(1, &rendererId);
        glDeleteTextures(1, &colorAttachmentId);
        glDeleteTextures(1, &depthAttachmentId);
        depthAttachmentId = 0;
        //LOG_DEBUG("Resetting framebuffer");
    }
    
    //LOG_INFO("{} x {}", width, height);

    glGenFramebuffers(1, &rendererId);
    glBindFramebuffer(GL_FRAMEBUFFER, rendererId);

    glGenTextures(1, &colorAttachmentId);
    glBindTexture(GL_TEXTURE_2D, colorAttachmentId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachmentId, 0);

    glGenTextures(1, &depthAttachmentId);
    glBindTexture(GL_TEXTURE_2D, depthAttachmentId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachmentId, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG_ERROR("Incomplete framebuffer {}", glGetError());
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, rendererId);
    //glViewport(0, 0, width, height);
}

void FrameBuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
}
