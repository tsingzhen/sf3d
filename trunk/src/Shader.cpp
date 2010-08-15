
#include <sf3d/Shader.hpp>

#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

namespace sf3d
{
    Shader::Shader(ShaderType type, const sf::String& filename)
        :   myType(type)
    {
        if (type == VERTEX_SHADER)
            myShader = glCreateShader(GL_VERTEX_SHADER);
        else
            myShader = glCreateShader(GL_FRAGMENT_SHADER);

        if (!filename.IsEmpty())
            LoadFromFile(filename);
    }

    Shader::~Shader()
    {
        glDeleteShader(myShader);
    }

    void    Shader::LoadFromFile(const sf::String& filename)
    {
        std::fstream file;
        file.open(filename.ToAnsiString().c_str());
        if (file.fail())
        {
            return;
        }


        std::stringstream bufStr;
        bufStr << file.rdbuf();
        file.close();

        const char* buffer = bufStr.str().c_str();
        glShaderSource(myShader, 1, &buffer, NULL);

        glCompileShader(myShader);
        GLint status, logSize;
        glGetShaderiv(myShader, GL_COMPILE_STATUS, &status);

        if (status != GL_TRUE)
        {
            glGetShaderiv(myShader, GL_INFO_LOG_LENGTH, &logSize);
            char* log = new char[logSize + 1];
            memset(log, 0, logSize + 1);
            glGetShaderInfoLog(myShader, logSize, &logSize, log);

            std::cerr << "Unable to compile ";
            if (myType == VERTEX_SHADER)
                std::cerr << "vertex";
            else
                std::cerr << "fragment";

            std::cerr << " shader. Reason :" << std::endl;
            std::cerr << log << std::endl;
            delete[] log;
            return;
        }
    }

    // Program class
    Program::Program(const sf::String& vertex, const sf::String& fragment)
        :   myIsLinked(false)
    {
        myProgram = glCreateProgram();

        if (!vertex.IsEmpty())
        {
            Shader vShader(Shader::VERTEX_SHADER, vertex);
            Attach(vShader);
        }
        if (!fragment.IsEmpty())
        {
            Shader fShader(Shader::FRAGMENT_SHADER, fragment);
            Attach(fShader);
        }

        if (!fragment.IsEmpty() || !vertex.IsEmpty())
            Link();
    }

    Program::~Program()
    {
        glDeleteProgram(myProgram);
    }

    void    Program::Attach(Shader& shader)
    {
        glAttachShader(myProgram, shader.myShader);
    }

    void    Program::Detach(Shader& shader)
    {
        glDetachShader(myProgram, shader.myShader);
    }

    bool    Program::Link()
    {
        if (myIsLinked)
            return true;

        glLinkProgram(myProgram);

        GLint status, logSize;
        glGetProgramiv(myProgram, GL_LINK_STATUS, &status);

        if (status != GL_TRUE)
        {
            glGetProgramiv(myProgram, GL_INFO_LOG_LENGTH, &logSize);
            char* log = new char[logSize + 1];
            memset(log, 0, logSize + 1);
            glGetProgramInfoLog(myProgram, logSize, &logSize, log);
            std::cerr << "Unable to link shaders to the program. Reason : " << std::endl;
            std::cerr << log << std::endl;
            myIsLinked = false;
        }

        myIsLinked = true;
        return myIsLinked;
    }

    void    Program::Use(Program& program)
    {
        if (!program.myIsLinked)
            return;

        glUseProgram(program.myProgram);

        sf::Uint8 i = 0;
        for (TextureMap::const_iterator it = program.myTextures.begin(); it != program.myTextures.end(); ++it)
        {
            glUniform1i(it->first, i);
            glActiveTextureARB(GL_TEXTURE0_ARB + i);
            glBindTexture(GL_TEXTURE_2D, it->second->GetID());
            ++i;
        }

        glActiveTextureARB(GL_TEXTURE0_ARB);
    }

    void    Program::Deactivate()
    {
        glUseProgram(0);
    }

    void    Program::Send(const sf::String& name, Texture& texture)
    {
        if (!myIsLinked)
            return;

        GLint loc = glGetUniformLocation(myProgram, name.ToAnsiString().c_str());
        glUseProgram(myProgram);

        myTextures[loc] = &texture;
    }

    void    Program::Send(const sf::String& name, const sf::Color& color)
    {
        if (!myIsLinked)
            return;

        float fcolor[4] = { static_cast<float>(color.r) / 255.f,
                            static_cast<float>(color.g) / 255.f,
                            static_cast<float>(color.b) / 255.f,
                            static_cast<float>(color.a) / 255.f };

        GLint loc = glGetUniformLocation(myProgram, name.ToAnsiString().c_str());
        glUseProgram(myProgram);

        glUniform4fv(loc, 4, fcolor);
    }

    void    Program::Send(const sf::String& name, const sf::Vector3f& vector)
    {
        if (!myIsLinked)
            return;

        GLint loc = glGetUniformLocation(myProgram, name.ToAnsiString().c_str());
        glUseProgram(myProgram);

        glUniform3f(loc, vector.x, vector.y, vector.z);
    }


    void    Program::Send(const sf::String& name, float f1, float f2, float f3, float f4)
    {
        if (!myIsLinked)
            return;

        GLint loc = glGetUniformLocation(myProgram, name.ToAnsiString().c_str());
        glUseProgram(myProgram);

        glUniform4f(loc, f1, f2, f3, f4);
    }

    void    Program::Send(const sf::String& name, sf::Uint32 value)
    {
        if (!myIsLinked)
            return;

        GLint loc = glGetUniformLocation(myProgram, name.ToAnsiString().c_str());
        glUseProgram(myProgram);
        glUniform1i(loc, value);
    }

    void    Program::Send(const sf::String& name, float value)
    {
        if (!myIsLinked)
            return;

        GLint loc = glGetUniformLocation(myProgram, name.ToAnsiString().c_str());
        glUseProgram(myProgram);
        glUniform1f(loc, value);
    }
}
