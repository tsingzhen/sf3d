
#include <sf3d/Material.hpp>

namespace sf3d
{
    Material::Materials   Material::myMaterials;

    Material::Material()
        :   ambientColor(sf::Color(123, 123, 123)),
            diffuseColor(sf::Color(255, 255, 255)),
            specularColor(sf::Color(0, 0, 0)),
            emissiveColor(sf::Color(0, 0, 0)),
            reflectiveMode(REFLECTION_NONE),
            refractive(false),
            smooth(false)
    {

    }

    Material&   Material::Get(const sf::String& name)
    {
        return myMaterials[name];
    }
}
