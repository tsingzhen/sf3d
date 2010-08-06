#ifndef SF3D_ANIMATEDMESHNODE_HPP
#define SF3D_ANIMATEDMESHNODE_HPP

#include <SFML/System/Clock.hpp>
#include <sf3d/Node.hpp>
#include <sf3d/MeshBuffer.hpp>

namespace sf3d
{
    class AnimatedMeshNode : public Node
    {
        public:
            AnimatedMeshNode(MeshBuffers* buffers);

            void            SetMeshBuffers(MeshBuffers* buffers);
            MeshBuffers*    GetMeshBuffers();

            void            SetFrame(sf::Uint32 frame);

            void            Play();
            void            Pause();
            void            Stop();
            void            SetLoop(bool loop = true);

            virtual void    Render(Node::RenderPass pass);

        private:
            void            UpdateAnim();

            sf::Uint32      myFrame;
            bool            myIsPlaying;
            bool            myIsLooping;
            MeshBuffers     *myMeshBuffers;

            sf::Clock       myClock;
    };
}
#endif // SF3D_ANIMATEDMESHNODE_HPP
