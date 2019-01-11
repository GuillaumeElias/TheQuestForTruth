#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template<typename T>
class Singleton {
private:
    static T* Instance;

public:
    Singleton() 
    { 
        Instance = this; 
    }
    static T* instance();
};

template<typename T>
T* Singleton<T>::instance()
{
    return Instance;
}

template<typename T>
T* Singleton<T>::Instance = nullptr;

#endif
