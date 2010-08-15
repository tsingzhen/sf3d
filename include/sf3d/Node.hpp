
#ifndef SF3D_NODE_HPP
#define SF3D_NODE_HPP

#include <SFML/System/Vector3.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <sf3d/Light.hpp>
#include <sf3d/Shader.hpp>

namespace sf3d
{
    class Node;
    typedef std::vector<Node*>  Nodes;

    class Node
    {
        public:
            typedef enum
            {
                PASS_REFLECTION_1 = 0,
                PASS_REFLECTION_2,
                PASS_NON_REFRACTIVE,
                PASS_SOLID,

                PASS_MULTITEXTURING,

                PASS_COUNT
            }   RenderPass;


            Node(const sf::String& name);

            void                SetName(const sf::String& name);
            const sf::String&   GetName() const;

            void                SetPosition(const sf::Vector3f& position);
            const sf::Vector3f& GetPosition() const;

            void                Move(const sf::Vector3f& move);

            void                SetRotation(const sf::Vector3f& rotation);
            const sf::Vector3f& GetRotation() const;

            void                Rotate(const sf::Vector3f& rotate);

            void                SetScale(const sf::Vector3f& scale);
            const sf::Vector3f& GetScale() const;

            void                Scale(const sf::Vector3f& scale);

            void                SetTexture(const sf::Image& image);
            sf::Image&          GetTexture();

            void                SetProgram(const Program& program);
            Program&            GetProgram();

            void                Add(Node* node);
            void                Remove(Node* node);

            Nodes&              GetChildren();

            void                SetMaterial(const sf::String& name);
            const sf::String&   GetMaterial() const;

            void                ApplyLighting(Lights& lights);

            virtual void        Render(RenderPass pass) {};

        protected:
            void                ApplyTransform();
            void                ApplyMaterial();
            void                ApplyTexture();
            void                ApplyProgram();

            bool                HandlePass(RenderPass pass);

            void                RenderChildren(RenderPass pass);

        private:
            struct
            {
                bool operator() (Light* l1, Light* l2) { return l1->GetBrightness() > l2->GetBrightness(); }
            } SortLights;

            // identity
            sf::String          myName;

            // world coordinates
            sf::Vector3f        myPosition, myRotation, myScale;

            // Parent / children
            Nodes               myChildren;
            Node*               myParent;

            // Materials
            sf::String          myMaterial;
            sf::Image           myTexture;
            Program             myProgram;
    };

}
#endif // SF3D_NODE_HPP
