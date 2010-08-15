#ifndef SF3D_FPSCAMERA_HPP
#define SF3D_FPSCAMERA_HPP

#include <sf3d/Camera.hpp>

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

    };
}
#endif // SF3D_FPSCAMERA_HPP
