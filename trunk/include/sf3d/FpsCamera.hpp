#ifndef SF3D_FPSCAMERA_HPP
#define SF3D_FPSCAMERA_HPP

#include <sf3d/Camera.hpp>

#include <SFML/System/Clock.hpp>

namespace sf3d
{
    class FpsCamera : public Camera
    {
        public:
            FpsCamera();

            void    StrafeLeft();
            void    StrafeRight();

            void    GotoUp();
            void    GotoDown();
            void    GotoLeft();
            void    GotoRight();

            virtual void    Render(Node::RenderPass pass);

        private:
            sf::Clock   myClock;

    };
}
#endif // SF3D_FPSCAMERA_HPP
