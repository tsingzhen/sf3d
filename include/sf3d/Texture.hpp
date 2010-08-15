#ifndef SF3D_TEXTURE_HPP
#define SF3D_TEXTURE_HPP

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <sf3d/GL/glew.h>
#include <sf3d/Utils.hpp>

namespace sf3d
{
    class Texture
    {
        public:
            Texture(const sf::Vector2ui& size, const sf::Color& color = sf::Color(0, 0, 0));
            Texture(const sf::String& filename);
            Texture(const sf::Image& image);

            // copy constructor
            Texture(const Texture& texture);

            ~Texture();

            void                Create();

            sf::Uint32          GetID() const;

            void                Render() const;

            const sf::Vector2ui&    GetSize() const;

        private:
            GLuint              myTextureID;
            sf::Image           myImage;
            sf::Vector2ui       mySize;

    };

    typedef std::vector<Texture>    Textures;
}

#endif // SF3D_TEXTURE_HPP
