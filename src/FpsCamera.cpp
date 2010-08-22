#include <sf3d/FpsCamera.hpp>

#include <sf3d/Utils.hpp>
#include <sf3d/Renderer.hpp>

#include <iostream>

namespace sf3d
{
    FpsCamera::FpsCamera()
        :   Camera()
    {

    }

    void    FpsCamera::StrafeLeft()
    {
        float yRad = GetRotation().y / 180 * pi;

        sf::Vector3f pos = GetPosition();
        pos.x += std::cos(yRad);
        pos.z += std::sin(yRad);
        SetPosition(pos);
    }

    void    FpsCamera::StrafeRight()
    {
        float yRad = GetRotation().y / 180 * pi;
        sf::Vector3f pos = GetPosition();
        pos.x -= std::cos(yRad);
        pos.z -= std::sin(yRad);
        SetPosition(pos);
    }

    void    FpsCamera::GotoUp()
    {
        float yRad = GetRotation().y / 180 * pi;
        float xRad = GetRotation().x / 180 * pi;
        sf::Vector3f pos = GetPosition();
        pos.x -= std::sin(yRad);
        pos.z += std::cos(yRad);
        pos.y += std::sin(xRad);
        SetPosition(pos);
    }

    void    FpsCamera::GotoDown()
    {
        float yRad = GetRotation().y / 180 * pi;
        float xRad = GetRotation().x / 180 * pi;
        sf::Vector3f pos = GetPosition();
        pos.x += std::sin(yRad);
        pos.z -= std::cos(yRad);
        pos.y -= std::sin(xRad);
        SetPosition(pos);
    }

    void    FpsCamera::GotoLeft()
    {
        sf::Vector3f pos = GetRotation();
        pos.y -= 1;
        if (pos.y < -360)
            pos.y += 360;
        SetRotation(pos);
    }

    void    FpsCamera::GotoRight()
    {
        sf::Vector3f pos = GetRotation();
        pos.y += 1;
        if (pos.y > 360)
            pos.y -= 360;
        SetRotation(pos);
    }

    void    FpsCamera::Render(Node::RenderPass pass)
    {
        sf::RenderWindow* win = Renderer::GetSingleton().GetWindow();

        Camera::Render(pass);

        myClock.Reset();

        if (win->GetInput().IsKeyDown(sf::Key::Left))
            GotoLeft();

        if (win->GetInput().IsKeyDown(sf::Key::Right))
            GotoRight();

        if (win->GetInput().IsKeyDown(sf::Key::Up) || win->GetInput().IsKeyDown(sf::Key::W))
            GotoUp();

        if (win->GetInput().IsKeyDown(sf::Key::Down) || win->GetInput().IsKeyDown(sf::Key::S))
            GotoDown();

        if (win->GetInput().IsKeyDown(sf::Key::D))
            StrafeRight();

        if (win->GetInput().IsKeyDown(sf::Key::A))
            StrafeLeft();

        if (win->GetInput().IsKeyDown(sf::Key::PageDown))
            Move(sf::Vector3f(0, 1, 0));
        else if (win->GetInput().IsKeyDown(sf::Key::PageUp))
            Move(sf::Vector3f(0, -1, 0));
    }
}
