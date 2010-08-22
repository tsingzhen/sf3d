#ifndef SF3D_MESHNODE_HPP
#define SF3D_MESHNODE_HPP

#include <sf3d/Node.hpp>

namespace sf3d
{
    class MeshBuffer;

    class MeshNode : public Node
    {
        public:
            MeshNode(MeshBuffer* meshBuffer);

            void            SetMeshBuffer(MeshBuffer* meshBuffer);
            MeshBuffer*     GetMeshBuffer() const;

            virtual void    Render(Node::RenderPass pass);

        private:
            MeshBuffer      *myMeshBuffer;

    };

}
#endif // SF3D_MESHNODE_HPP
