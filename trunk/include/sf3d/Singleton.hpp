#ifndef SF3D_SINGLETON_HPP
#define SF3D_SINGLETON_HPP

namespace sf3d
{
    template<typename T>
    class Singleton
    {
        protected:
            Singleton() {};
            ~Singleton() {};

        public:
            static T*  GetSingletonPtr()
            {
                if (!myInstance)
                    myInstance = new T();
                return myInstance;
            }

            static T&  GetSingleton()
            {
                return *GetSingletonPtr();
            }

        private:
            static T*      myInstance;

    };

}
#endif // SF3D_SINGLETON_HPP
