
#include <sf3d/Renderer.hpp>
#include <sf3d/GL/glew.h>

#include <sf3d/Material.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

namespace sf3d
{
    template<>
    Renderer*   Singleton<Renderer>::myInstance = 0;

    Renderer::Renderer()
        :   myScene(0),
            myFrameBuffer(0),
            myProgram()
    {
    }

    Renderer::~Renderer()
    {
        delete myFrameBuffer;
    }

    void    Renderer::Init(sf::RenderWindow& window)
    {
        myWindow = &window;

        Material& matLight = Material::Get("Light");
        matLight.ambientColor = sf::Color(255, 255, 255);
        matLight.diffuseColor = sf::Color(255, 255, 255);
        matLight.specularColor = sf::Color(255, 255, 255);

        Material& matNode = Material::Get("Node");
        matNode.ambientColor = sf::Color(255, 255, 255);
        matNode.diffuseColor = sf::Color(123, 123, 123);
        matNode.specularColor = sf::Color(0, 0, 0);

        Resize();
    }

    sf::RenderWindow*   Renderer::GetWindow()
    {
        return myWindow;
    }

    void        Renderer::SetScene(Scene* scene)
    {
        myScene = scene;
    }

    Scene*      Renderer::GetScene()
    {
        return myScene;
    }

    void        Renderer::Resize()
    {
        sf::Vector2ui winSize(myWindow->GetWidth(), myWindow->GetHeight());

        glViewport(0, 0, winSize.x, winSize.y);

        delete myFrameBuffer;
        myFrameBuffer = new RenderBuffer(winSize);

        myTextures.push_back(Texture(winSize)); // 0 : reflection
        myTextures.push_back(Texture(winSize)); // 1 : refraction
        myTextures.push_back(Texture(winSize)); // 2 : scene
        myTextures.push_back(Texture(winSize)); // 3 : scene finale
    }

    Texture& Renderer::GetSceneTexture()
    {
        return myTextures[2];
    }

    Texture& Renderer::GetReflectionTexture()
    {
        return myTextures[0];
    }

    Texture& Renderer::GetDepthTexture()
    {
        return myFrameBuffer->GetDepthTexture();
    }

    Texture&    Renderer::GetRefractionTexture()
    {
        return myTextures[1];
    }

    void        Renderer::Display()
    {
        if (!myWindow || !myScene || !myFrameBuffer)
            return;

        myWindow->RestoreGLStates();

        RenderBuffer::Use(myFrameBuffer);
        const sf::Vector2ui winSize(myWindow->GetWidth(), myWindow->GetHeight());

//
        myFrameBuffer->Attach(myTextures[2]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        myScene->Render(Node::PASS_SOLID);

        RenderBuffer::Use(0);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);

        // Create 2D rendering for applying texture...
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(myWindow->GetView().GetMatrix().Get4x4Elements());

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        myTextures[2].Render();

        myWindow->SaveGLStates();


    }

    void    Renderer::SetProgram(const Program& program)
    {
        myProgram = program;
    }

    const Program&  Renderer::GetProgram() const
    {
        return myProgram;
    }
}
