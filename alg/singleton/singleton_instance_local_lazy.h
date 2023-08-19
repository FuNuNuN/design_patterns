///////////////////  普通懒汉式实现 -- 线程不安全 //////////////////
#include <mutex>    // std::mutex
#include <unistd.h> //sleep

class SingleInstanceLocalLazy {
public:
    // 获取单例对象
    static SingleInstanceLocalLazy &GetInstance();

    // 打印单例地址
    void Print();

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    SingleInstanceLocalLazy();
    ~SingleInstanceLocalLazy();

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    SingleInstanceLocalLazy(const SingleInstanceLocalLazy &signal);
    const SingleInstanceLocalLazy &operator=(const SingleInstanceLocalLazy &signal);
};

SingleInstanceLocalLazy &SingleInstanceLocalLazy::GetInstance()
{
    static SingleInstanceLocalLazy m_SingleInstanceLocalLazy;

    return m_SingleInstanceLocalLazy;
}

void SingleInstanceLocalLazy::Print()
{
    printf("我的实例内存地址是:%p \n", this);
}

SingleInstanceLocalLazy::SingleInstanceLocalLazy()
{
    printf("构造函数:\n");
}

SingleInstanceLocalLazy::~SingleInstanceLocalLazy()
{
    printf("析构函数:\n");
}

// 线程函数
void *SingleInstanceLocalLazyPrintHello(void *threadid)
{
    // 主线程与子线程分离，两者相互不干涉，子线程结束同时子线程的资源自动回收
    pthread_detach(pthread_self());

    // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
    int tid = *((int *)threadid);

    printf("Hi, 我是线程 ID[%d]\n", tid);

    // 打印实例地址
    SingleInstanceLocalLazy::GetInstance().Print();

    pthread_exit(NULL);
}