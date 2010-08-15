#ifndef SF3D_RENDERER_HPP
#define SF3D_RENDERER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderImage.hpp>
#include <SFML/Window/Context.hpp>

#include <sf3d/Singleton.hpp>
#include <sf3d/RenderBuffer.hpp>
#include <sf3d/Scene.hpp>

namespace sf3d
{
    class Renderer : public Singleton<Renderer>
    {
        public:
            friend Renderer&    Singleton<Renderer>::GetSingleton();
            friend Renderer*    Singleton<Renderer>::GetSingletonPtr();

            void                Init(sf::RenderWindow& window);
            sf::RenderWindow*   GetWindow();

            void                SetScene(Scene* scene);
            Scene*              GetScene();

            void                Resize();

            void                Display();

            void                SetProgram(const Program& program);
            const Program&      GetProgram() const;

            Texture&            GetDepthTexture();
            Texture&            GetSceneTexture();
            Texture&            GetReflectionTexture();
            Texture&            GetRefractionTexture();

        protected:
            Renderer();
            ~Renderer();

        private:
            void                RenderMultiTexture();

            sf::RenderWindow    *myWindow;
            Scene               *myScene;

            RenderBuffer        *myFrameBuffer;
            Program             myProgram;
            Textures            myTextures;
    };
}
#endif // SF3D_RENDERER_HPP
