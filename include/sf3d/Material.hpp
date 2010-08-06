
#ifndef SF3D_MATERIAL_HPP
#define SF3D_MATERIAL_HPP

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>

#include <map>

namespace sf3d
{
    class Material
    {
        public:
            Material();

            sf::Color       ambientColor, diffuseColor, specularColor, emissiveColor;

            static Material&    Get(const sf::String& name);

        private:
            typedef std::map<sf::String, Material>  Materials;

            static Materials    myMaterials;

    };
}
#endif // SF3D_MATERIAL_HPP
