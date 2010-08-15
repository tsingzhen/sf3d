
#include <sf3d/MeshNode.hpp>
#include <sf3d/MeshBuffer.hpp>

#include <sf3d/GL/glew.h>
#include <sf3d/Material.hpp>

#include <iostream>

namespace sf3d
{
    MeshNode::MeshNode(MeshBuffer* meshBuffer)
        :   Node("MeshNode"),
            myMeshBuffer(meshBuffer)
    {
    }


    MeshBuffer* MeshNode::GetMeshBuffer() const
    {
        return myMeshBuffer;
    }

    void    MeshNode::Render(Node::RenderPass pass)
    {
        if (!HandlePass(pass))
            return;

        if (!myMeshBuffer)
            return;

        glPushMatrix();

        ApplyTransform();
        ApplyMaterial();
        ApplyTexture();
        ApplyProgram();

        glEnableClientState(GL_VERTEX_ARRAY);
        myMeshBuffer->Use(MeshBuffer::VERTEX_BUFFER);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glEnableClientState(GL_NORMAL_ARRAY);
        myMeshBuffer->Use(MeshBuffer::NORMAL_BUFFER);
        glNormalPointer(GL_FLOAT, 0, 0);

        glEnableClientState(GL_COLOR_ARRAY);
        myMeshBuffer->Use(MeshBuffer::COLOR_BUFFER);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, 0);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        myMeshBuffer->Use(MeshBuffer::TEXTURE_BUFFER);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);

        myMeshBuffer->Use(MeshBuffer::INDEX_BUFFER);
        glDrawElements(GL_TRIANGLES, myMeshBuffer->GetTriangles().size() * 3, GL_UNSIGNED_INT, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        RenderChildren(pass);

        Program::Deactivate();

        glPopMatrix();
    }

}
