
#include <sf3d/AnimatedMeshNode.hpp>

#include <sf3d/Material.hpp>

namespace sf3d
{
    AnimatedMeshNode::AnimatedMeshNode(MeshBuffers* meshBuffers)
        :   Node("AnimatedMeshNode"),
            myFrame(0),
            myIsPlaying(false),
            myIsLooping(false),
            myMeshBuffers(meshBuffers)
    {

    }

    void    AnimatedMeshNode::SetMeshBuffers(MeshBuffers* buffers)
    {
        myMeshBuffers = buffers;
    }

    MeshBuffers*  AnimatedMeshNode::GetMeshBuffers()
    {
        return myMeshBuffers;
    }

    void    AnimatedMeshNode::SetFrame(sf::Uint32 frame)
    {
        myFrame = frame;
    }

    void    AnimatedMeshNode::Play()
    {
        myIsPlaying = true;
    }

    void    AnimatedMeshNode::Pause()
    {
        myIsPlaying = false;
    }

    void    AnimatedMeshNode::Stop()
    {
        myIsPlaying = false;
        myFrame = 0;
        myClock.Reset();
    }

    void    AnimatedMeshNode::SetLoop(bool loop)
    {
        myIsLooping = loop;
    }

    void    AnimatedMeshNode::UpdateAnim()
    {
        if (!myIsPlaying)
            return;

        ++myFrame;
        if (myFrame >= myMeshBuffers->size())
        {
            if (myIsLooping)
                myFrame = 0;
            else
                Stop();
        }
    }

    void    AnimatedMeshNode::Render(Node::RenderPass pass)
    {
        if (!HandlePass(pass))
            return;

        UpdateAnim();

        if (myMeshBuffers->size() == 0)
            return;

        MeshBuffer* mb = (*myMeshBuffers)[myFrame];
        if (!mb)
            return;
        mb->Update();

        glPushMatrix();

        ApplyTransform();
        ApplyTexture();
        ApplyProgram();

        glEnableClientState(GL_VERTEX_ARRAY);
        mb->Use(MeshBuffer::VERTEX_BUFFER);
        glVertexPointer(3, GL_FLOAT, 0, 0);


        ApplyMaterial();

        glEnableClientState(GL_NORMAL_ARRAY);
        mb->Use(MeshBuffer::NORMAL_BUFFER);
        glNormalPointer(GL_FLOAT, 0, 0);

        glEnableClientState(GL_COLOR_ARRAY);
        mb->Use(MeshBuffer::COLOR_BUFFER);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, 0);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        mb->Use(MeshBuffer::TEXTURE_BUFFER);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);

        mb->Use(MeshBuffer::INDEX_BUFFER);
        glDrawElements(GL_TRIANGLES, mb->GetTriangles().size() * 3, GL_UNSIGNED_INT, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glDisable(GL_TEXTURE_2D);

        RenderChildren(pass);

        glPopMatrix();

    }
}
