
#include <sf3d/TerrainNode.hpp>

#include <sf3d/MeshBuffer.hpp>

namespace sf3d
{
    TerrainNode::TerrainNode(const sf::Image& heightMap)
        :   MeshNode(new MeshBuffer()),
            myHeightMap(heightMap),
            myPrecision(1)
    {
        mySize.x = heightMap.GetWidth();
        mySize.y = heightMap.GetHeight();

        myRenderList = glGenLists(1);

        Compute();
    }

    TerrainNode::~TerrainNode()
    {
        glDeleteLists(myRenderList, 1);
    }

    void    TerrainNode::SetPrecision(sf::Uint32 precision)
    {
        myPrecision = precision;
    }

    sf::Uint32  TerrainNode::GetPrecision() const
    {
        return myPrecision;
    }

    float   TerrainNode::GetPointHeight(sf::Uint32 pointX, sf::Uint32 pointY)
    {
        return static_cast<float>(myHeightMap.GetPixel(pointX, pointY).r);
    }

    sf::Uint32  TerrainNode::GetIndexFromPoint(sf::Uint32 pointX, sf::Uint32 pointY)
    {
        return pointY * mySize.y + pointX;
    }

    void    TerrainNode::Compute()
    {
        MeshBuffer* mb = GetMeshBuffer();
        MeshBuffer::Vertices vertices;
        MeshBuffer::Vertex v;
        MeshBuffer::Triangle t;

        sf::Uint32 offset = 0;
        for (sf::Uint32 y = 0; y < mySize.y; y += myPrecision)
        {
            for (sf::Uint32 x = 0; x < mySize.x; x += myPrecision)
            {
                v.pos = sf::Vector3f(x, GetPointHeight(x, y), y);
                v.texCoord = sf::Vector2f(static_cast<float>(x) / mySize.x, static_cast<float>(y) / mySize.y);
                vertices.push_back(v);
            }
        }


        for (sf::Uint32 y = 0; y < mySize.y - myPrecision; y += myPrecision)
        {
            for (sf::Uint32 x = 0; x < mySize.x - myPrecision; x += myPrecision)
            {
                t.vIndex[0] = GetIndexFromPoint(x, y);
                t.vIndex[1] = GetIndexFromPoint(x, y + 1);
                t.vIndex[2] = GetIndexFromPoint(x + 1, y + 1);
                mb->GetTriangles().push_back(t);

                t.vIndex[0] = GetIndexFromPoint(x, y);
                t.vIndex[1] = GetIndexFromPoint(x + 1, y + 1);
                t.vIndex[2] = GetIndexFromPoint(x + 1, y);
                mb->GetTriangles().push_back(t);

            }
        }

        mb->SetVertices(vertices);

        mb->Allocate();
    }

}
