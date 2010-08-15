
#include <sf3d/Texture.hpp>
#include <SFML/Graphics/Renderer.hpp>

#include <iostream>

namespace sf3d
{
    Texture::Texture(const sf::Vector2ui& size, const sf::Color& color)
        :   myTextureID(0),
            myImage(),
            mySize(size)
    {
        glGenTextures(1, &myTextureID);

        myImage.Create(mySize.x, mySize.y, color);
        Create();
    }

    Texture::Texture(const sf::String& filename)
        :   myTextureID(0),
            myImage()
    {
        glGenTextures(1, &myTextureID);

        myImage.LoadFromFile(filename);
        Create();
    }

    Texture::Texture(const sf::Image& image)
        :   myTextureID(0),
            myImage(image)
    {
        glGenTextures(1, &myTextureID);
        Create();
    }

    Texture::Texture(const Texture& texture)
    {
        glGenTextures(1, &myTextureID);
        mySize = texture.mySize;
        myImage = texture.myImage;

        Create();
    }

    void    Texture::Create()
    {
        mySize.x = myImage.GetWidth();
        mySize.y = myImage.GetHeight();

        glBindTexture(GL_TEXTURE_2D, myTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myImage.GetWidth(), myImage.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, myImage.GetPixelsPtr());

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    sf::Uint32  Texture::GetID() const
    {
        return static_cast<sf::Uint32>(myTextureID);
    }

    void    Texture::Render() const
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, myTextureID);
        glColor3ub(255, 255, 255);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
            glTexCoord2f(0, 0); glVertex3f(0, mySize.y, 0);
            glTexCoord2f(1, 0); glVertex3f(mySize.x, mySize.y, 0);
            glTexCoord2f(1, 1); glVertex3f(mySize.x, 0, 0);
        glEnd();
    }

    const sf::Vector2ui&    Texture::GetSize() const
    {
        return mySize;
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &myTextureID);
    }

}
