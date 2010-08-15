#ifndef SF3D_SHADER_HPP
#define SF3D_SHADER_HPP

#include <SFML/System/String.hpp>

#include <sf3d/GL/glew.h>
#include <sf3d/Texture.hpp>

#include <map>

namespace sf3d
{
    class Shader
    {
        public:
            friend class Program;

            typedef enum
            {
                VERTEX_SHADER,
                FRAGMENT_SHADER
            }   ShaderType;

            Shader(ShaderType type, const sf::String& filename = sf::String());
            ~Shader();

            void        LoadFromFile(const sf::String& filename);

        private:
            GLuint      myShader;
            ShaderType  myType;
    };

    class Program
    {
        public:
            Program(const sf::String& vertex = sf::String(), const sf::String& fragment = sf::String());
            ~Program();


            void    Attach(Shader& shader);
            void    Detach(Shader& shader);

            bool    Link();

            void    Send(const sf::String& name, Texture& texture);
            void    Send(const sf::String& name, sf::Uint32 value);
            void    Send(const sf::String& name, float value);
            void    Send(const sf::String& name, const sf::Color& color);
            void    Send(const sf::String& name, const sf::Vector3f& vect);
            void    Send(const sf::String& name, float f1, float f2, float f3, float f4);

            static void Deactivate();

            static void Use(Program& program);

        private:
            typedef std::map<sf::Int32, Texture*>   TextureMap;

            GLuint      myProgram;
            bool        myIsLinked;
            TextureMap  myTextures;
    };
}
#endif // SF3D_SHADER_HPP
