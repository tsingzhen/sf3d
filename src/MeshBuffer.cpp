
#include <sf3d/MeshBuffer.hpp>

#include <sf3d/Utils.hpp>

namespace sf3d
{
    MeshBuffer::MeshBuffer()
    {
        glGenBuffers(1, &myVertexBufferID);
        glGenBuffers(1, &myColorBufferID);
        glGenBuffers(1, &myNormalBufferID);
        glGenBuffers(1, &myTextureBufferID);
        glGenBuffers(1, &myIndexBufferID);
    }

    MeshBuffer::~MeshBuffer()
    {
        glDeleteBuffers(1, &myVertexBufferID);
        glDeleteBuffers(1, &myColorBufferID);
        glDeleteBuffers(1, &myNormalBufferID);
        glDeleteBuffers(1, &myTextureBufferID);
        glDeleteBuffers(1, &myIndexBufferID);
    }

    void    MeshBuffer::SetVertices(const Vertices& vertices)
    {
        myVertices = vertices;
    }

    MeshBuffer::Triangles&  MeshBuffer::GetTriangles()
    {
        return myTriangles;
    }

    MeshBuffer::Vertices&   MeshBuffer::GetVertices()
    {
        return myVertices;
    }

    MeshBuffer::Normals&    MeshBuffer::GetNormals()
    {
        return myNormals;
    }

    void    MeshBuffer::Use(BufferType type)
    {
        if (type == VERTEX_BUFFER)
            glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
        else if (type == COLOR_BUFFER)
            glBindBuffer(GL_ARRAY_BUFFER, myColorBufferID);
        else if (type == NORMAL_BUFFER)
            glBindBuffer(GL_ARRAY_BUFFER, myNormalBufferID);
        else if (type == TEXTURE_BUFFER)
            glBindBuffer(GL_ARRAY_BUFFER, myTextureBufferID);
        else if (type == COLOR_BUFFER)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndexBufferID);
        else
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        return;
    }

    void    MeshBuffer::Update()//bool smooth)
    {
        sf::Uint32 vertexSize = myVertices.size(), indexSize = myTriangles.size() * 3;
        sf::Uint32 v = 0, n = 0, t = 0, c = 0, i = 0;

        float* vertices = new float[vertexSize * 3];
        float* normals = new float[vertexSize * 3];
        float* texCoords = new float[vertexSize * 2];
        sf::Uint8* colors = new sf::Uint8[vertexSize * 4];
        sf::Uint32* indexes = new sf::Uint32[indexSize];

        for (Vertices::const_iterator it = myVertices.begin(); it != myVertices.end(); ++it)
        {
            const Vertex& vertex = *it;

            vertices[v + 0] = vertex.pos.x;
            vertices[v + 1] = vertex.pos.y;
            vertices[v + 2] = vertex.pos.z;
            v += 3;

            normals[n + 0] = vertex.normal.x;
            normals[n + 1] = vertex.normal.y;
            normals[n + 2] = vertex.normal.z;
            n += 3;

            colors[c + 0] = vertex.color.r;
            colors[c + 1] = vertex.color.g;
            colors[c + 2] = vertex.color.b;
            colors[c + 3] = vertex.color.a;
            c += 4;

            texCoords[t + 0] = vertex.texCoord.x;
            texCoords[t + 1] = vertex.texCoord.y;
            t += 2;
        }

        for (Triangles::const_iterator it = myTriangles.begin(); it != myTriangles.end(); ++it)
        {
            const Triangle& triangle = *it;
            indexes[i + 0] = triangle.vIndex[0];
            indexes[i + 1] = triangle.vIndex[1];
            indexes[i + 2] = triangle.vIndex[2];

            i += 3;
        }

        glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize * 3 * sizeof(float), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, myNormalBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize * 3 * sizeof(float), normals);

        glBindBuffer(GL_ARRAY_BUFFER, myColorBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize * 4 * sizeof(sf::Uint8), colors);

        glBindBuffer(GL_ARRAY_BUFFER, myTextureBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize * 2 * sizeof(float), texCoords);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndexBufferID);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexSize * sizeof(float), indexes);


        delete[] vertices;
        delete[] normals;
        delete[] texCoords;
        delete[] colors;
        delete[] indexes;
    }

    void    MeshBuffer::ComputeNormals()
    {
        for (Triangles::iterator it = myTriangles.begin(); it != myTriangles.end(); ++it)
        {
            Triangle& t = *it;
            sf::Vector3f v[3] = { myVertices[t.vIndex[0]].pos, myVertices[t.vIndex[1]].pos, myVertices[t.vIndex[2]].pos };
            t.normal = Utils::Vect_CrossProduct(v[1] - v[0], v[2] - v[0]);

            for (sf::Uint8 i = 0; i < 3; ++i)
            {
                sf::Vector3f a = v[(i + 1) % 3] - v[i];
                sf::Vector3f b = v[(i + 2) % 3] - v[i];
                float weigth = std::acos(Utils::Vect_DotProduct(a, b) / (Utils::Vect_GetLength(a) * Utils::Vect_GetLength(b)));
                myVertices[t.vIndex[i]].normal += weigth * t.normal;
            }
        }

        for (Vertices::iterator it = myVertices.begin(); it != myVertices.end(); ++it)
        {
            Vertex& v = *it;
            v.normal = Utils::Vect_Normalize(v.normal);
        }
    }

    void    MeshBuffer::Allocate()
    {
        sf::Uint32 vertexSize = myVertices.size(), indexSize = myTriangles.size() * 3;

        glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertexSize * 3 * sizeof(float), 0, GL_STREAM_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, myNormalBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertexSize * 3 * sizeof(float), 0, GL_STREAM_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, myColorBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertexSize * 4 * sizeof(sf::Uint8), 0, GL_STREAM_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, myTextureBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertexSize * 2 * sizeof(float), 0, GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(sf::Uint32), 0, GL_STREAM_DRAW);

        ComputeNormals();
        Update();
    }
}
