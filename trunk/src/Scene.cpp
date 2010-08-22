
#include <sf3d/Scene.hpp>

#include <sf3d/Renderer.hpp>
#include <sf3d/GL/glew.h>
#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderImage.hpp>

#include <sf3d/Camera.hpp>

namespace sf3d
{
    Scene::Scene(Camera* camera)
        :   Node("Scene"),
            myCamera(camera),
            myShowBasis(false)
    {
    }

    void    Scene::ShowBasis(bool show)
    {
        myShowBasis = show;
    }

    void    Scene::SetCamera(Camera* camera)
    {
        myCamera = camera;
    }

    Camera* Scene::GetCamera() const
    {
        return myCamera;
    }

    void    Scene::Render(Node::RenderPass pass)
    {
        Nodes& nodes = (pass == PASS_MULTITEXTURING ? myLastNodes : GetChildren());

        ApplyTransform();

        if (!myCamera)
            return;

        myCamera->Render(pass);

        // Draw with stencil buffer
        if (pass == Node::PASS_REFLECTION_1)
        {
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
            glDepthMask(GL_FALSE);

            glEnable(GL_STENCIL_TEST);

            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        }
        else if (pass == Node::PASS_REFLECTION_2)
        {
            glEnable(GL_DEPTH_TEST);

            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            glDepthMask(GL_TRUE);

            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_EQUAL, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

            glEnable(GL_LIGHTING);
            glScalef(1, -1, 1);
        }
        else if (pass == Node::PASS_SOLID)
        {
            glDisable(GL_STENCIL_TEST);
            glEnable(GL_DEPTH_TEST);

            /*
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/

/*
            GLfloat fogColor[] = {0.5, 0.5, 0.5};
            glEnable(GL_FOG);
            glFogi(GL_FOG_MODE, GL_LINEAR);
            glFogfv(GL_FOG_COLOR, fogColor);
            glFogf(GL_FOG_DENSITY, 0.3);
            glFogf(GL_FOG_START, 10);
            glFogf(GL_FOG_END, 200);
*/

            if (myShowBasis)
            {
                glBegin(GL_LINES);
                    glColor3ub(255, 0, 0);
                    glVertex3f(0, 0, 0);
                    glVertex3f(1, 0, 0);

                    glColor3ub(0, 255, 0);
                    glVertex3f(0, 0, 0);
                    glVertex3f(0, 1, 0);

                    glColor3ub(0, 0, 255);
                    glVertex3f(0, 0, 0);
                    glVertex3f(0, 0, 1);
                glEnd();
            }

            glEnable(GL_LIGHTING);
        }


        for (Nodes::iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            Node* n = *it;

            ApplyProgram();

            n->ApplyLighting(myLights);
            n->Render(pass);
        }
    }

    void    Scene::AddWater(WaterNode& water)
    {
        myLastNodes.push_back(&water);
    }

    void    Scene::AddLight(Light* light)
    {
        myLights.push_back(light);
    }
}
