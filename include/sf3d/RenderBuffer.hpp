
#ifndef SF3D_RENDERBUFFER_HPP
#define SF3D_RENDERBUFFER_HPP

#include <sf3d/GL/glew.h>
#include <sf3d/Texture.hpp>
#include <sf3d/Utils.hpp>

#include <SFML/Window/Context.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sf3d
{
    class RenderBuffer
    {
        public:
            RenderBuffer(const sf::Vector2ui& size);
            ~RenderBuffer();

            void            Attach(const Texture& texture);

            Texture&        GetDepthTexture();

            static void     Use(RenderBuffer* frameBuffer);

        private:
            GLuint          myFrameBuffer;
            Texture         myDepthTexture;
            sf::Vector2ui   mySize;
    };
}
#endif // SF3D_TEXTUREBUFFER_HPP
