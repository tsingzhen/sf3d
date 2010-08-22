#ifndef SF3D_LIGHT_HPP
#define SF3D_LIGHT_HPP

#include <SFML/System/String.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>

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

            void                SetAmbientColor(const sf::Color& ambient);
            const sf::Color&    GetAmbientColor() const;

            void                SetDiffuseColor(const sf::Color& diffuse);
            const sf::Color&    GetDiffuseColor() const;

            void                SetSpecularColor(const sf::Color& specular);
            const sf::Color&    GetSpecularColor() const;

            void                ComputeBrightness(const sf::Vector3f& position);
            float               GetBrightness() const;

            static void         Sort(Light* l1, Light* l2);

        private:
            sf::Vector3f        myPosition;
            float               myBrightness;

            sf::Color           myAmbientColor, myDiffuseColor, mySpecularColor;

    };

    typedef std::vector<Light*> Lights;
}

#endif // SF3D_LIGHT_HPP
