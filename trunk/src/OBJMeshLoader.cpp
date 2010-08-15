
#include <sf3d/OBJMeshLoader.hpp>

#include <sf3d/Utils.hpp>

#include <fstream>
#include <iostream>
#include <boost/tokenizer.hpp>



namespace sf3d
{
    OBJMeshLoader::OBJMeshLoader()
    {

    }

    MeshBuffer* OBJMeshLoader::Load(const sf::String& filename)
    {
        std::fstream file(filename.ToAnsiString().c_str());
        if (file.fail())
        {
            std::cerr << "Unable to load mesh file \"" << filename.ToAnsiString() << "\" " << std::endl;
            return 0;
        }

        MeshBuffer* mb = new MeshBuffer();
        MeshBuffer::Vertices& vertices = mb->GetVertices();
        MeshBuffer::Triangles& triangles = mb->GetTriangles();
        MeshBuffer::Normals& normals = mb->GetNormals();

        std::string line;
        while (std::getline(file, line))
        {
            switch (line[0])
            {
                case 'v' :
                {
                    switch (line[1])
                    {
                        case ' ':
                        {
                            const sf::Vector3f& vpos = GetVectorFromLine(line);
                            MeshBuffer::Vertex v;
                            v.pos = vpos;
                            v.color = sf::Color(255, 255, 255);
                            vertices.push_back(v);
                        }
                        break;

                        case 'n':
                        {
                            const sf::Vector3f& normal = GetVectorFromLine(line);
                            normals.push_back(normal);
                        }
                    };
                }
                break;

                case 'f' :
                {
                    const MeshBuffer::Triangle& t = GetTriangleFromLine(line);
                    triangles.push_back(t);
                }
                break;
            };
        }

        mb->Allocate();
        return mb;
    }

    sf::Vector3f            OBJMeshLoader::GetVectorFromLine(const std::string& line)
    {
        sf::Vector3f vec;

        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        boost::char_separator<char> sep(" ");
        tokenizer token(line, sep);

        sf::Uint8 i = 0;
        for (tokenizer::iterator it = token.begin(); it != token.end(); ++it)
        {
            if (i == 1)
                vec.x = Utils::GetFromString<float>(*it, 0.f);
            else if (i == 2)
                vec.y = Utils::GetFromString<float>(*it, 0.f);
            else if (i == 3)
                vec.z = Utils::GetFromString<float>(*it, 0.f);
            ++i;
        }
        return vec;
    }

    MeshBuffer::Triangle    OBJMeshLoader::GetTriangleFromLine(const std::string& line)
    {
        MeshBuffer::Triangle t;

        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        boost::char_separator<char> sep(" "), sep2("/", "", boost::keep_empty_tokens);
        tokenizer token1(line, sep);

        // Get all elements as string
        sf::Uint8 i = 0;
        for (tokenizer::iterator it1 = token1.begin(); it1 != token1.end(); ++it1)
        {
            const std::string& element = *it1;

            if (i != 0)
            {
                tokenizer token2(element, sep2);
                tokenizer::iterator it2 = token2.begin();

                t.vIndex[i - 1] = Utils::GetFromString<sf::Uint32>(*it2, 0) - 1; ++it2;
                if (it2 != token2.end())
                {
                    //std
                    ++it2;
                }

                if (it2 != token2.end())
                {
                    sf::Uint32 nIndex = Utils::GetFromString<sf::Uint32>(*it2, 0) - 1;
                    t.normalIndex[i - 1] = nIndex;
                }


            }
            ++i;
        }
        return t;
    }
}
