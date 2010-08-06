
#include <sf3d/MeshNode.hpp>
#include <sf3d/MeshBuffer.hpp>

#include <sf3d/GL/glew.h>

namespace sf3d
{
    MeshNode::MeshNode(MeshBuffer* meshBuffer)
        :   Node("MeshNode"),
            myMeshBuffer(meshBuffer)
    {
    }

    void    MeshNode::Render(Node::RenderPass pass)
    {
        if (!myMeshBuffer)
            return;

        glPushMatrix();

        ApplyTransform();
        ApplyMaterial();

        myMeshBuffer->Update();

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

/*
        // immediat mode
        glBegin(GL_TRIANGLES);
        const MeshBuffer::Triangles& triangles = myMeshBuffer->GetTriangles();
        const MeshBuffer::Vertices& vertices = myMeshBuffer->GetVertices();
        for (MeshBuffer::Triangles::const_iterator it = triangles.begin(); it != triangles.end(); ++it)
        {
            const MeshBuffer::Triangle& triangle = *it;
            for (sf::Uint8 i = 0; i < 3; ++i)
            {
                const MeshBuffer::Vertex& v = vertices[triangle.vIndex[i]];
                glNormal3f(v.normal.x, v.normal.y, v.normal.z);
                glVertex3f(v.pos.x, v.pos.y, v.pos.z);
            }
        }
        glEnd();
*/

        RenderChildren(pass);

        glPopMatrix();
    }
}
