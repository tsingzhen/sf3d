
#include <sf3d/Scene.hpp>

#include <sf3d/Renderer.hpp>
#include <sf3d/GL/glew.h>
#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderImage.hpp>

namespace sf3d
{
    Scene::Scene(Camera& camera)
        :   Node("Scene"),
            myCamera(camera),
            myShowBasis(false)
    {
    }

    void    Scene::ShowBasis(bool show)
    {
        myShowBasis = show;
    }

    void    Scene::SetCamera(Camera& camera)
    {
        myCamera = camera;
    }

    Camera& Scene::GetCamera()
    {
        return myCamera;
    }

    void    Scene::Render(Node::RenderPass pass)
    {
        Nodes& nodes = (pass == PASS_MULTITEXTURING ? myLastNodes : GetChildren());

        ApplyTransform();

        myCamera.Render(pass);

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
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        if (pass == PASS_MULTITEXTURING)
        {
            for (Nodes::iterator it = myLastNodes.begin(); it != myLastNodes.end(); ++it)
            {
                Node* n = *it;

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                n->ApplyLighting(myLights);
                n->Render(pass);
            }
        }
        else
        {
            for (Nodes::iterator it = nodes.begin(); it != nodes.end(); ++it)
            {
                Node* n = *it;

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                n->ApplyLighting(myLights);
                n->Render(pass);
            }
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
