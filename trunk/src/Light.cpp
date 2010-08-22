
#include <sf3d/Light.hpp>
#include <sf3d/Utils.hpp>

namespace sf3d
{
    Light::Light()
        :   myPosition(),
            myAmbientColor(sf::Color(255, 255, 255)),
            myDiffuseColor(sf::Color(255, 255, 255)),
            mySpecularColor(sf::Color(0, 0, 0))
    {

    }

    void    Light::ComputeBrightness(const sf::Vector3f& nodePosition)
    {
        sf::Vector3f d = myPosition - nodePosition;
        myBrightness = Utils::Vect_GetLength(d);
    }

    float   Light::GetBrightness() const
    {
        return myBrightness;
    }

    void    Light::SetPosition(const sf::Vector3f& position)
    {
        myPosition = position;
    }

    const sf::Vector3f& Light::GetPosition() const
    {
        return myPosition;
    }

    void    Light::Move(const sf::Vector3f& move)
    {
        myPosition += move;
    }

    void    Light::SetAmbientColor(const sf::Color& ambient)
    {
        myAmbientColor = ambient;
    }

    const sf::Color&    Light::GetAmbientColor() const
    {
        return myAmbientColor;
    }

    void    Light::SetDiffuseColor(const sf::Color& diffuse)
    {
        myDiffuseColor = diffuse;
    }

    const sf::Color&    Light::GetDiffuseColor() const
    {
        return myDiffuseColor;
    }

    void    Light::SetSpecularColor(const sf::Color& specular)
    {
        mySpecularColor = specular;
    }

    const sf::Color&    Light::GetSpecularColor() const
    {
        return mySpecularColor;
    }
}
