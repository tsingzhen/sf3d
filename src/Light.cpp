
#include <sf3d/Light.hpp>
#include <sf3d/Utils.hpp>

namespace sf3d
{
    Light::Light()
        :   myPosition(),
            myMaterial("Light")
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

    void    Light::SetMaterial(const sf::String& material)
    {
        myMaterial = material;
    }

    const sf::String&   Light::GetMaterial() const
    {
        return myMaterial;
    }
}
