#ifndef SF3D_UTILS_HPP
#define SF3D_UTILS_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/String.hpp>

#include <sstream>
#include <cmath>

#include <iostream>
#include <sf3d/GL/glew.h>

namespace sf
{
    typedef Vector2<Uint32> Vector2ui;
}

namespace sf3d
{
    const float pi = 3.141592654f;

    class Utils
    {
        public:
            template<typename T>
            static T            GetFromString(const sf::String& strValue, const T& defaultValue)
            {
                std::istringstream iss(strValue.ToAnsiString());
                T back;
                if (iss >> back)
                    return back;
                return defaultValue;
            }

            template<typename T>
            static sf::String   ToString(const T& value)
            {
                std::ostringstream oss;
                oss << value;
                return oss.str();
            }

            static sf::Vector3f Vect_CrossProduct(const sf::Vector3f& v1, const sf::Vector3f& v2)
            {
                sf::Vector3f vect;
                vect.x = v1.y * v2.z - v1.z * v2.y;
                vect.y = v1.z * v2.x - v1.x * v2.z;
                vect.z = v1.x * v2.y - v1.y * v2.x;
                return vect;
            }

            static float    Vect_GetLength(const sf::Vector3f& vect)
            {
                return std::sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
            }

            static float    Vect_GetLengthSq(const sf::Vector3f& vect)
            {
                return vect.x * vect.x + vect.y * vect.y + vect.z * vect.z;
            }

            static float    Vect_DotProduct(const sf::Vector3f& v1, const sf::Vector3f& v2)
            {
                return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
            }

            static sf::Vector3f Vect_Normalize(const sf::Vector3f vect)
            {
                float length = Vect_GetLength(vect);
                sf::Vector3f v;
                v.x = vect.x / length;
                v.y = vect.y / length;
                v.z = vect.z / length;
                return v;
            }

            static bool CheckGLError(const sf::String& func)
            {
                GLuint status = glGetError();
                if (status == GL_NO_ERROR)
                {
                    std::cout << "No error in " << func.ToAnsiString() << std::endl;
                    return true;
                }
                else if (status == GL_INVALID_ENUM)
                    std::cerr << "GL_invalid_enum";
                else if (status == GL_INVALID_VALUE)
                    std::cerr << "GL_invalid_value";
                else if (status == GL_INVALID_OPERATION)
                    std::cerr << "GL_invalid_operation";
                else if (status == GL_STACK_OVERFLOW)
                    std::cerr << "GL_stack_overflow";
                else if (status == GL_STACK_UNDERFLOW)
                    std::cerr << "GL_stack_underflow";
                else if (status == GL_OUT_OF_MEMORY)
                    std::cerr << "GL_out_of_memory";

                std::cerr << "in func " << func.ToAnsiString() << std::endl;
                return false;
            }

        protected:
            Utils();

    };
}
#endif // SF3D_UTILS_HPP
