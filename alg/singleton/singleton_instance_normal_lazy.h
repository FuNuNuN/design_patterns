///////////////////  普通懒汉式实现 -- 线程不安全 //////////////////
#include <mutex>    // std::mutex
#include <unistd.h> //sleep

class SingleInstanceNormalLazy {
public:
    // 获取单例对象
    static SingleInstanceNormalLazy *GetInstance();

    // 释放单例，进程退出时调用
    static void deleteInstance();

    // 打印单例地址
    void Print();

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    SingleInstanceNormalLazy();
    ~SingleInstanceNormalLazy();

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    SingleInstanceNormalLazy(const SingleInstanceNormalLazy &signal);
    const SingleInstanceNormalLazy &operator=(const SingleInstanceNormalLazy &signal);

private:
    // 唯一单例对象指针
    static SingleInstanceNormalLazy *m_SingleInstanceNormalLazy;
};

// 初始化静态成员变量
SingleInstanceNormalLazy *SingleInstanceNormalLazy::m_SingleInstanceNormalLazy = NULL;

SingleInstanceNormalLazy *SingleInstanceNormalLazy::GetInstance()
{
    if (m_SingleInstanceNormalLazy == NULL) {
        sleep(1);
        m_SingleInstanceNormalLazy = new (std::nothrow) SingleInstanceNormalLazy; // 没有加锁是线程不安全的，当线程并发时会创建多个实例
    }

    return m_SingleInstanceNormalLazy;
}

void SingleInstanceNormalLazy::deleteInstance()
{
    if (m_SingleInstanceNormalLazy) {
        delete m_SingleInstanceNormalLazy;
        m_SingleInstanceNormalLazy = NULL;
    }
}

void SingleInstanceNormalLazy::Print()
{
    printf("我的实例内存地址是:%p \n", this);
}

SingleInstanceNormalLazy::SingleInstanceNormalLazy()
{
    printf("构造函数:\n");
}

SingleInstanceNormalLazy::~SingleInstanceNormalLazy()
{
    printf("析构函数:\n");
}

// 线程函数
void *PrintHello(void *threadid)
{
    // 主线程与子线程分离，两者相互不干涉，子线程结束同时子线程的资源自动回收
    pthread_detach(pthread_self());

    // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
    int tid = *((int *)threadid);

    printf("Hi, 我是线程 ID[%d]\n", tid);

    // 打印实例地址
    SingleInstanceNormalLazy::GetInstance()->Print();

    pthread_exit(NULL);
}