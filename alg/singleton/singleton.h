#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton {
public:
    template <typename... Args>
    static T &GetInstance(Args... args)
    {
        static T instance{args...};
        return instance;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;

public:
    Singleton(Singleton const &) = delete;
    Singleton &operator=(Singleton const &) = delete;
};
#endif