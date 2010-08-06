
#include <sf3d/Node.hpp>

#include <sf3d/GL/glew.h>
#include <sf3d/Material.hpp>

#include <algorithm>
#include <cmath>

#include <iostream>

#define MAX_LIGHTS  (8)

namespace sf3d
{
    Node::Node(const sf::String& name)
        :   myName("Node"),
            myPosition(),
            myRotation(),
            myScale(sf::Vector3f(1, 1, 1)),
            myParent(0),
            myMaterial("DefaultNode"),
            myTexture()
    {

    }

    void    Node::SetName(const sf::String& name)
    {
        myName = name;
    }

    const sf::String&   Node::GetName() const
    {
        return myName;
    }

    void    Node::SetPosition(const sf::Vector3f& position)
    {
        myPosition = position;
    }

    const sf::Vector3f& Node::GetPosition() const
    {
        return myPosition;
    }

    void    Node::Move(const sf::Vector3f& move)
    {
        myPosition += move;
    }

    void    Node::SetRotation(const sf::Vector3f& rotation)
    {
        myRotation = rotation;
    }

    const sf::Vector3f& Node::GetRotation() const
    {
        return myRotation;
    }

    void    Node::Rotate(const sf::Vector3f& rotate)
    {
        myRotation += rotate;
    }

    void    Node::SetScale(const sf::Vector3f& scale)
    {
        myScale = scale;
    }

    const sf::Vector3f& Node::GetScale() const
    {
        return myScale;
    }

    void    Node::Scale(const sf::Vector3f& scale)
    {
        myScale += scale;
    }

    void    Node::SetTexture(const sf::Image& texture)
    {
        myTexture = texture;
    }

    sf::Image&  Node::GetTexture()
    {
        return myTexture;
    }

    void    Node::ApplyTexture()
    {
        glEnable(GL_TEXTURE_2D);
        myTexture.Bind();
    }

    void    Node::Add(Node* node)
    {
        if (!node)
            return;

        node->myParent = this;
        myChildren.push_back(node);
    }

    void    Node::Remove(Node* node)
    {
        for (Nodes::iterator it = myChildren.begin(); it != myChildren.end(); ++it)
        {
            if (node == *it)
            {
                node->myParent = 0;
                it = myChildren.erase(it);
            }
        }
    }

    Nodes&  Node::GetChildren()
    {
        return myChildren;
    }

    void    Node::RenderChildren(RenderPass pass)
    {
        for (Nodes::iterator it = myChildren.begin(); it != myChildren.end(); ++it)
        {
            Node* n = *it;
            n->Render(pass);
        }
    }

    void    Node::ApplyTransform()
    {
        glTranslatef(myPosition.x, myPosition.y, myPosition.z);
        glRotatef(myRotation.x, 1, 0, 0);
        glRotatef(myRotation.y, 0, 1, 0);
        glRotatef(myRotation.z, 0, 0, 1);
        glScalef(myScale.x, myScale.y, myScale.z);
    }

    void    Node::SetMaterial(const sf::String& material)
    {
        myMaterial = material;
    }

    const sf::String&   Node::GetMaterial() const
    {
        return myMaterial;
    }

    void    Node::ApplyMaterial()
    {
        const Material& mat = Material::Get(myMaterial);

        GLfloat ambient[] = { static_cast<GLfloat>(mat.ambientColor.r) / 255.f,
                              static_cast<GLfloat>(mat.ambientColor.g) / 255.f,
                              static_cast<GLfloat>(mat.ambientColor.b) / 255.f,
                              static_cast<GLfloat>(mat.ambientColor.a) / 255.f };

        GLfloat diffuse[] = { static_cast<GLfloat>(mat.diffuseColor.r) / 255.f,
                              static_cast<GLfloat>(mat.diffuseColor.g) / 255.f,
                              static_cast<GLfloat>(mat.diffuseColor.b) / 255.f,
                              static_cast<GLfloat>(mat.diffuseColor.a) / 255.f };

        GLfloat specular[] = { static_cast<GLfloat>(mat.specularColor.r) / 255.f,
                               static_cast<GLfloat>(mat.specularColor.g) / 255.f,
                               static_cast<GLfloat>(mat.specularColor.b) / 255.f,
                               static_cast<GLfloat>(mat.specularColor.a) / 255.f };

        GLfloat emissive[] = { static_cast<GLfloat>(mat.emissiveColor.r) / 255.f,
                               static_cast<GLfloat>(mat.emissiveColor.g) / 255.f,
                               static_cast<GLfloat>(mat.emissiveColor.b) / 255.f,
                               static_cast<GLfloat>(mat.emissiveColor.a) / 255.f};

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
    }

    void    Node::ApplyLighting(Lights& lights)
    {
        // Get nearest lights
        for (Lights::iterator it = lights.begin(); it != lights.end(); ++it)
        {
            (*it)->ComputeBrightness(myPosition);
        }

        std::sort(lights.begin(), lights.end(), SortLights);
        int nbLights = lights.size();
        sf::Uint32 maxLights = std::min(MAX_LIGHTS, nbLights);
        for (sf::Uint8 i = 0; i < maxLights; ++i)
        {
            Light* l = lights[i];

            glEnable(GL_LIGHT0 + i);

            const Material& mat = Material::Get(myMaterial);

            GLfloat ambient[] = { static_cast<GLfloat>(mat.ambientColor.r) / 255.f,
                                  static_cast<GLfloat>(mat.ambientColor.g) / 255.f,
                                  static_cast<GLfloat>(mat.ambientColor.b) / 255.f,
                                  static_cast<GLfloat>(mat.ambientColor.a) / 255.f };

            GLfloat diffuse[] = { static_cast<GLfloat>(mat.diffuseColor.r) / 255.f,
                                  static_cast<GLfloat>(mat.diffuseColor.g) / 255.f,
                                  static_cast<GLfloat>(mat.diffuseColor.b) / 255.f,
                                  static_cast<GLfloat>(mat.diffuseColor.a) / 255.f };

            GLfloat specular[] = { static_cast<GLfloat>(mat.specularColor.r) / 255.f,
                                   static_cast<GLfloat>(mat.specularColor.g) / 255.f,
                                   static_cast<GLfloat>(mat.specularColor.b) / 255.f,
                                   static_cast<GLfloat>(mat.specularColor.a) / 255.f };

            const sf::Vector3f& pos = l->GetPosition();
            GLfloat position[] = { pos.x, pos.y, pos.z, 1.f };

            glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient);
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse);
            glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular);
            glLightfv(GL_LIGHT0 + i, GL_POSITION, position);

            glBegin(GL_LINES);
                glColor3ub(255, 0, 0);
                glVertex3f(pos.x, pos.y, pos.z);
                glVertex3f(0, 0, 0);
            glEnd();
        }
    }

}
