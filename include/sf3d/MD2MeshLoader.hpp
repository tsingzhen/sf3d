#ifndef SF3D_MD2MESHLOADER_HPP
#define SF3D_MD2MESHLOADER_HPP

#include <SFML/System/String.hpp>

#include <sf3d/MeshBuffer.hpp>

namespace sf3d
{
    class MD2MeshLoader
    {
        public:
            MD2MeshLoader();

            MeshBuffers*    Load(const sf::String& filename);

        private:

            typedef struct
            {
                sf::Uint32  ident, version;
                sf::Uint32  textureWidth, textureHeight;
                sf::Uint32  frameSize;
                sf::Uint32  nbSkins, nbVertices, nbTexCoords, nbTriangles, nbGLCmds, nbFrames;
                sf::Uint32  offSkins, offTexCoords, offTriangles, offFrames, offGLCmds, offEnd;
            }   MD2Header;

            typedef float   vec3[3];

            typedef struct
            {
                sf::Uint8   vpos[3];
                sf::Uint8   normalIndex;
            }   MD2Vertex;

            typedef struct
            {
                sf::Uint16  vertex[3];
                sf::Uint16  st[3];
            }   MD2Triangle;

            typedef struct
            {
                sf::Int16   s, t;
            }   MD2TexCoord;

            typedef struct
            {
                vec3        scale, translate;
                char        name[16];
                MD2Vertex   *vertices;
            }   MD2Frame;

            typedef struct
            {
                char        name[68];
            }   MD2Skin;

    };
}
#endif // SF3D_MD2MESHLOADER_HPP
