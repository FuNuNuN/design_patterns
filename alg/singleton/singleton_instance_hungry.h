///////////////////  饿汉式实现 //////////////////
#include <pthread.h>
#include <stdio.h>

class SingleInstanceHungry {
public:
    // 获取单例对象
    static SingleInstanceHungry *GetInstance();

    // 释放单例，进程退出时调用
    static void deleteInstance();

    // 打印单例地址
    void Print();

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    SingleInstanceHungry();
    ~SingleInstanceHungry();

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    SingleInstanceHungry(const SingleInstanceHungry &signal);
    const SingleInstanceHungry &operator=(const SingleInstanceHungry &signal);

private:
    // 唯一单例对象指针
    static SingleInstanceHungry *m_SingleInstanceHungry;
};

// 初始化静态成员变量
SingleInstanceHungry *SingleInstanceHungry::m_SingleInstanceHungry = new (std::nothrow) SingleInstanceHungry;

SingleInstanceHungry *SingleInstanceHungry::GetInstance()
{
    return m_SingleInstanceHungry;
}

void SingleInstanceHungry::deleteInstance()
{
    if (m_SingleInstanceHungry) {
        delete m_SingleInstanceHungry;
        m_SingleInstanceHungry = NULL;
    }
}

void SingleInstanceHungry::Print()
{
    printf("我的实例内存地址是:%p \n", this);
}

SingleInstanceHungry::SingleInstanceHungry()
{
    printf("构造函数:\n");
}

SingleInstanceHungry::~SingleInstanceHungry()
{
    printf("析构函数:\n");
}

// 线程函数
void *SingleInstanceHungryPrintHello(void *threadid)
{
    // 主线程与子线程分离，两者相互不干涉，子线程结束同时子线程的资源自动回收
    pthread_detach(pthread_self());

    // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
    int tid = *((int *)threadid);

    printf("Hi, 我是线程 ID[%d]\n", tid);

    // 打印实例地址
    SingleInstanceHungry::GetInstance()->Print();

    pthread_exit(NULL);
}