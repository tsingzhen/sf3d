
#ifndef SF3D_TERRAINNODE_HPP
#define SF3D_TERRAINNODE_HPP

#include <sf3d/MeshNode.hpp>

namespace sf3d
{
    class TerrainNode : public MeshNode
    {
        public:
            TerrainNode(const sf::Image& heightMap);
            ~TerrainNode();

            void            SetPrecision(sf::Uint32 precision);
            sf::Uint32      GetPrecision() const;

            void            Compute();

        private:
            float           GetPointHeight(sf::Uint32 pointX, sf::Uint32 pointY);
            sf::Uint32      GetIndexFromPoint(sf::Uint32 pointX, sf::Uint32 pointY);

            sf::Image       myHeightMap;
            sf::Vector2ui   mySize;
            sf::Uint32      myPrecision;
            GLuint          myRenderList;
    };
}

#endif // SF3D_TERRAINNODE_HPP