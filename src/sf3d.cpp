
#include <sf3d.hpp>

namespace sf3d
{
    void    Init()
    {
        glewInit();

        Material& matLight = Material::Get("Light");
        matLight.ambientColor = sf::Color(123, 123, 123);
        matLight.diffuseColor = sf::Color(255, 255, 255);
        matLight.specularColor = sf::Color(0, 0, 0);
        matLight.emissiveColor = sf::Color(0, 0, 0);
    }
}
