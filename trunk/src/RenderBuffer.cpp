
#include <sf3d/RenderBuffer.hpp>

#include <iostream>

using namespace std;

namespace sf3d
{
    RenderBuffer::RenderBuffer(const sf::Vector2ui& size)
        :   myDepthTexture(size, sf::Color(0,0,0)),
            mySize(size)
    {
        glGenFramebuffersEXT(1, &myFrameBuffer);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, myFrameBuffer);

        // Create the depth stencil texture
        glBindTexture(GL_TEXTURE_2D, myDepthTexture.GetID());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8_EXT, size.x, size.y, 0, GL_DEPTH_STENCIL_EXT, GL_UNSIGNED_INT_24_8_EXT, 0);

        // Attach it to the fbo
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, myDepthTexture.GetID(), 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_2D, myDepthTexture.GetID(), 0);

        GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
        if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
        {
            if (status == GL_FRAMEBUFFER_UNSUPPORTED_EXT)
                std::cerr << "Wrong texture format !" << std::endl;
            else if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT)
                std::cerr << "Incomplete attachment !" << std::endl;
            else if (status == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT)
                std::cerr << "Dimensions are wrong !" << std::endl;
            else if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT)
                std::cerr << "No images are attached to fbo !" << std::endl;
        }

        Use(0);
    }

    RenderBuffer::~RenderBuffer()
    {
        glDeleteFramebuffersEXT(1, &myFrameBuffer);
    }

    void    RenderBuffer::Use(RenderBuffer* frameBuffer)
    {
        if (frameBuffer)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBuffer->myFrameBuffer);
        }
        else
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        }
    }

    void    RenderBuffer::Attach(const Texture& texture)
    {
        // Attach the texture to the fbo
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture.GetID(), 0);
    }

    Texture&  RenderBuffer::GetDepthTexture()
    {
        return myDepthTexture;
    }

}
