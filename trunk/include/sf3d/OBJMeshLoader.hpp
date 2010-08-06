
#ifndef SF3D_OBJMESHLOADER_HPP
#define SF3D_OBJMESHLOADER_HPP

#include <SFML/System/String.hpp>
#include <sf3d/MeshBuffer.hpp>

namespace sf3d
{
    class OBJMeshLoader
    {
        public :
            OBJMeshLoader();

            MeshBuffer*             Load(const sf::String& filename);

        private:
            sf::Vector3f            GetVectorFromLine(const std::string& line);
            MeshBuffer::Triangle    GetTriangleFromLine(const std::string& line);
    };
}

#endif // SF3D_OBJMESHLOADER_HPP
