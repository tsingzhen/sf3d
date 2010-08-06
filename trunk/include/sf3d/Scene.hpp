
#ifndef SF3D_SCENE_HPP
#define SF3D_SCENE_HPP

#include <sf3d/Node.hpp>
#include <sf3d/Camera.hpp>
#include <sf3d/Light.hpp>

namespace sf3d
{
    class Scene : public Node
    {
        public:
            Scene();

            void            ShowBasis(bool show = true);

            void            SetCamera(const Camera& camera);
            Camera&         GetCamera();

            void            AddLight(Light* light);

            virtual void    Render(Node::RenderPass pass);

        private:
            Lights          myLights;
            Camera          myCamera;
            bool            myShowBasis;
    };
}
#endif // SF3D_SCENE_HPP
