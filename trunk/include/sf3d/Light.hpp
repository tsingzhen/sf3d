#ifndef SF3D_LIGHT_HPP
#define SF3D_LIGHT_HPP

#include <SFML/System/String.hpp>
#include <SFML/System/Vector3.hpp>

#include <vector>

namespace sf3d
{
    class Light
    {
        public:
            Light();

            void                SetPosition(const sf::Vector3f& position);
            const sf::Vector3f& GetPosition() const;

            void                Move(const sf::Vector3f& move);

            void                SetMaterial(const sf::String& material);
            const sf::String&   GetMaterial() const;

            void                ComputeBrightness(const sf::Vector3f& position);
            float               GetBrightness() const;

            static void         Sort(Light* l1, Light* l2);

        private:
            sf::Vector3f        myPosition;
            sf::String          myMaterial;

            float               myBrightness;

    };

    typedef std::vector<Light*> Lights;
}

#endif // SF3D_LIGHT_HPP
