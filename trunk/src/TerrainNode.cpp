
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

        Compute();
    }

    TerrainNode::~TerrainNode()
    {

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

    void    TerrainNode::Compute()
    {
        MeshBuffer* mb = GetMeshBuffer();

        MeshBuffer::Vertices& vertices = mb->GetVertices();
        MeshBuffer::Triangles& triangles = mb->GetTriangles();
        MeshBuffer::Vertex v;
        MeshBuffer::Triangle t;

        float offset = 0;
        sf::Uint32 x, y;
        for (y = 0; y < mySize.y; y += myPrecision)
        {
            for (x = 0; x < mySize.x; x += myPrecision)
            {
                v.pos = sf::Vector3f(x, GetPointHeight(x, y), y);
                v.color = sf::Color(255, 255, 255);
                v.texCoord = sf::Vector2f(static_cast<float>(x) / mySize.x, static_cast<float>(y) / mySize.y);
                vertices.push_back(v);
            }
        }
        offset = std::ceil(static_cast<float>(mySize.y) / static_cast<float>(myPrecision));

        sf::Uint32 i = 0;
        for (y = 0; y < mySize.y; y += myPrecision)
        {
            for (x = 0; x < mySize.x; x += myPrecision)
            {
                if (x < mySize.x - myPrecision && y < mySize.y - myPrecision)
                {
                    t.vIndex[0] = i;
                    t.vIndex[1] = i + 1 + offset;
                    t.vIndex[2] = i + 1;
                    triangles.push_back(t);

                    t.vIndex[0] = i;
                    t.vIndex[1] = i + offset;
                    t.vIndex[2] = i + offset + 1;
                    triangles.push_back(t);
                }
                ++i;
            }
        }
        mb->Allocate();
    }

    void    TerrainNode::Render(Node::RenderPass pass)
    {
        glEnable(GL_CULL_FACE);

        MeshNode::Render(pass);

        glDisable(GL_CULL_FACE);
    }

}
