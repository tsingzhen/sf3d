
#ifndef SF3D_SCENE_HPP
#define SF3D_SCENE_HPP

#include <sf3d/Node.hpp>
#include <sf3d/Camera.hpp>
#include <sf3d/Light.hpp>
#include <sf3d/Texture.hpp>
#include <sf3d/WaterNode.hpp>

namespace sf3d
{
    class Scene : public Node
    {
        public:
            Scene(Camera& camera);

            void            ShowBasis(bool show = true);

            void            SetCamera(Camera& camera);
            Camera&         GetCamera();

            void            AddLight(Light* light);
            void            AddWater(WaterNode& water);

            virtual void    Render(Node::RenderPass pass);

        private:
            friend class    Renderer;

            Nodes           myLastNodes;
            Lights          myLights;
            Camera&         myCamera;
            bool            myShowBasis;

            Textures        myTextures;
    };
}
#endif // SF3D_SCENE_HPP
