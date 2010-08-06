#ifndef SF3D_CAMERA_HPP
#define SF3D_CAMERA_HPP

#include <sf3d/Node.hpp>

namespace sf3d
{
    class Camera
    {
        public:
            Camera();

            void                SetPosition(const sf::Vector3f& position);
            const sf::Vector3f& GetPosition() const;

            void                Move(const sf::Vector3f& move);

            void                SetRotation(const sf::Vector3f& rotation);
            const sf::Vector3f& GetRotation() const;

            void                Rotate(const sf::Vector3f& rotate);

            void                SetTarget(const sf::Vector3f& target);
            const sf::Vector3f& GetTarget() const;

            void                SetFOV(float fov);
            float               GetFOV() const;

            void                SetAspectRatio(float aspectRatio);
            float               GetAspectRatio() const;

            void                SetNearValue(float nearValue);
            float               GetNearValue() const;

            void                SetFarValue(float farValue);
            float               GetFarValue() const;

            virtual void        Render();

        private:
            float               myFOV;
            float               myNearValue, myFarValue;
            float               myAspectRatio;

            sf::Vector3f        myPosition, myRotation, myTarget;
    };
}
#endif // SF3D_CAMERA_HPP
