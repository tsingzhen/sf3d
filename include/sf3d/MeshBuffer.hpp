#ifndef SF3D_MESHBUFFER_HPP
#define SF3D_MESHBUFFER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>

#include <sf3d/GL/glew.h>

namespace sf3d
{
    class MeshBuffer
    {
        public:

            typedef struct
            {
                sf::Vector3f    pos;
                sf::Vector2f    texCoord;
                sf::Vector3f    normal;
                sf::Color       color;
            }   Vertex;

            typedef struct
            {
                sf::Uint32      vIndex[3];
                sf::Vector3f    normal;
                sf::Uint32      normalIndex[3];
            }   Triangle;

            typedef enum
            {
                NONE = 0,
                VERTEX_BUFFER,
                COLOR_BUFFER,
                TEXTURE_BUFFER,
                NORMAL_BUFFER,
                INDEX_BUFFER
            }   BufferType;

            typedef std::vector<Triangle>       Triangles;
            typedef std::vector<Vertex>         Vertices;
            typedef std::vector<sf::Vector3f>   Normals;

            MeshBuffer();
            ~MeshBuffer();

            void            SetVertices(const Vertices& vertices);

            Triangles&      GetTriangles();
            Vertices&       GetVertices();
            Normals&        GetNormals();

            void            Allocate();
            void            Update();
            void            ComputeNormals();

            void            Use(BufferType type);

        private:
            Triangles       myTriangles;
            Vertices        myVertices;
            Normals         myNormals;

            GLuint          myVertexBufferID;
            GLuint          myNormalBufferID;
            GLuint          myColorBufferID;
            GLuint          myTextureBufferID;
            GLuint          myIndexBufferID;
    };

    typedef std::vector<MeshBuffer*>    MeshBuffers;
}

#endif // SF3D_MESHBUFFER_HPP
