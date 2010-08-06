#include <sf3d/MD2MeshLoader.hpp>

#include <fstream>
#include <iostream>

#define MD2_IDENT   (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

namespace sf3d
{

    MD2MeshLoader::MD2MeshLoader()
    {

    }

    MeshBuffers* MD2MeshLoader::Load(const sf::String& filename)
    {
        MeshBuffers* buffers = new MeshBuffers();
        std::fstream file;

        file.open(filename.ToAnsiString().c_str(), std::ios::in | std::ios::binary);

        if (file.fail())
        {
            std::cerr << "Unable to load animated mesh file \"" << filename.ToAnsiString() << "\"" << std::endl;
            return buffers;
        }

        MD2Header header;
        file.read((char*)&header, sizeof(MD2Header));

        if (header.version != 8 || header.ident != MD2_IDENT)
        {
            file.close();
            std::cerr << "Corrupted MD2 file \"" << filename.ToAnsiString() << "\"" << std::endl;
            return buffers;
        }

        MD2Skin* skins = new MD2Skin[header.nbSkins];
        MD2TexCoord* texCoords = new MD2TexCoord[header.nbTexCoords];
        MD2Triangle* triangles = new MD2Triangle[header.nbTriangles];
        MD2Frame* frames = new MD2Frame[header.nbFrames];

        file.seekg(header.offSkins, std::ios::beg);
        file.read((char*)skins, sizeof(char) * 68 * header.nbSkins);

        file.seekg(header.offTexCoords, std::ios::beg);
        file.read((char*)texCoords, sizeof(MD2TexCoord) * header.nbTexCoords);

        file.seekg(header.offTriangles, std::ios::beg);
        file.read((char*)triangles, sizeof(MD2Triangle) * header.nbTriangles);

        file.seekg(header.offFrames, std::ios::beg);
        for (sf::Uint32 i = 0; i < header.nbFrames; ++i)
        {
            frames[i].vertices = new MD2Vertex[header.nbVertices];

            file.read((char*)&frames[i].scale, sizeof(vec3));
            file.read((char*)&frames[i].translate, sizeof(vec3));
            file.read((char*)&frames[i].name, sizeof(char) * 16);
            file.read((char*)frames[i].vertices, sizeof(MD2Vertex) * header.nbVertices);
        }
        file.close();

        // Creation des meshbuffers
        for (sf::Uint32 i = 0; i < header.nbFrames; ++i)
        {
            MeshBuffer* mb = new MeshBuffer();

            const MD2Frame& frame = frames[i];
            MeshBuffer::Vertices& mbVertices = mb->GetVertices();
            for (sf::Uint32 v = 0; v < header.nbVertices; ++v)
            {
                MeshBuffer::Vertex mbVertex;
                const MD2Vertex& vertex = frame.vertices[v];
                mbVertex.pos.x = vertex.vpos[0] * frame.scale[0] + frame.translate[0];
                mbVertex.pos.y = vertex.vpos[1] * frame.scale[1] + frame.translate[1];
                mbVertex.pos.z = vertex.vpos[2] * frame.scale[2] + frame.translate[2];
                mbVertex.color = sf::Color(255, 255, 255);
                mbVertices.push_back(mbVertex);
            }

            MeshBuffer::Triangles& mbTriangles = mb->GetTriangles();
            for (sf::Uint32 t = 0; t < header.nbTriangles; ++t)
            {
                MeshBuffer::Triangle mbTriangle;
                const MD2Triangle& triangle = triangles[t];
                mbTriangle.vIndex[0] = triangle.vertex[0];
                mbTriangle.vIndex[1] = triangle.vertex[1];
                mbTriangle.vIndex[2] = triangle.vertex[2];

                mbVertices[mbTriangle.vIndex[0]].texCoord.x = static_cast<float>(texCoords[triangle.st[0]].s) / header.textureWidth;
                mbVertices[mbTriangle.vIndex[0]].texCoord.y = static_cast<float>(texCoords[triangle.st[0]].t) / header.textureHeight;
                mbVertices[mbTriangle.vIndex[1]].texCoord.x = static_cast<float>(texCoords[triangle.st[1]].s) / header.textureWidth;
                mbVertices[mbTriangle.vIndex[1]].texCoord.y = static_cast<float>(texCoords[triangle.st[1]].t) / header.textureHeight;
                mbVertices[mbTriangle.vIndex[2]].texCoord.x = static_cast<float>(texCoords[triangle.st[2]].s) / header.textureWidth;
                mbVertices[mbTriangle.vIndex[2]].texCoord.y = static_cast<float>(texCoords[triangle.st[2]].t) / header.textureHeight;

                mbTriangles.push_back(mbTriangle);
            }

            mb->Allocate();
            buffers->push_back(mb);
        }

        delete[] skins;
        delete[] texCoords;
        delete[] triangles;
        for (sf::Uint32 i = 0; i < header.nbFrames; ++i)
        {
            delete[] frames[i].vertices;
        }
        delete[] frames;

        return buffers;
    }
}
