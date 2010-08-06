
#include <sf3d/Scene.hpp>

#include <sf3d/GL/glew.h>

namespace sf3d
{
    Scene::Scene()
        :   Node("Scene"),
            myCamera(),
            myShowBasis(false)
    {

    }

    void    Scene::ShowBasis(bool show)
    {
        myShowBasis = show;
    }

    void    Scene::SetCamera(const Camera& camera)
    {
        myCamera = camera;
    }

    Camera& Scene::GetCamera()
    {
        return myCamera;
    }

    void    Scene::Render(Node::RenderPass pass)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        ApplyTransform();
        myCamera.Render();

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

        Nodes& nodes = GetChildren();
        for (Nodes::iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            Node* n = *it;
            n->ApplyLighting(myLights);
            n->Render(pass);
        }

        glDisable(GL_LIGHTING);

    }

    void    Scene::AddLight(Light* light)
    {
        myLights.push_back(light);
    }
}
