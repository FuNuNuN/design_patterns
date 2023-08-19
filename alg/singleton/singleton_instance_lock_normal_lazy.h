///////////////////  普通懒汉式实现 -- 线程不安全 //////////////////
#include <mutex>    // std::mutex
#include <unistd.h> //sleep

class SingleInstanceLockNormalLazy {
public:
    // 获取单例对象
    static SingleInstanceLockNormalLazy *GetInstance();

    // 释放单例，进程退出时调用
    static void deleteInstance();

    // 打印单例地址
    void Print();

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    SingleInstanceLockNormalLazy();
    ~SingleInstanceLockNormalLazy();

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    SingleInstanceLockNormalLazy(const SingleInstanceLockNormalLazy &signal);
    const SingleInstanceLockNormalLazy &operator=(const SingleInstanceLockNormalLazy &signal);

private:
    static std::mutex m_Mutex;
    // 唯一单例对象指针
    static SingleInstanceLockNormalLazy *m_SingleInstanceLockNormalLazy;
};

std::mutex SingleInstanceLockNormalLazy::m_Mutex;
// 初始化静态成员变量
SingleInstanceLockNormalLazy *SingleInstanceLockNormalLazy::m_SingleInstanceLockNormalLazy = NULL;

SingleInstanceLockNormalLazy *SingleInstanceLockNormalLazy::GetInstance()
{
    //  这里使用了两个 if判断语句的技术称为双检锁；好处是，只有判断指针为空的时候才加锁，
    //  避免每次调用 GetInstance的方法都加锁，锁的开销毕竟还是有点大的。
    if (m_SingleInstanceLockNormalLazy == NULL) {
        std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
        if (m_SingleInstanceLockNormalLazy == NULL) {
            m_SingleInstanceLockNormalLazy = new (std::nothrow) SingleInstanceLockNormalLazy;
        }
    }

    return m_SingleInstanceLockNormalLazy;
}

void SingleInstanceLockNormalLazy::deleteInstance()
{
    std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
    if (m_SingleInstanceLockNormalLazy) {
        delete m_SingleInstanceLockNormalLazy;
        m_SingleInstanceLockNormalLazy = NULL;
    }
}

void SingleInstanceLockNormalLazy::Print()
{
    printf("我的实例内存地址是:%p \n", this);
}

SingleInstanceLockNormalLazy::SingleInstanceLockNormalLazy()
{
    printf("构造函数:\n");
}

SingleInstanceLockNormalLazy::~SingleInstanceLockNormalLazy()
{
    printf("析构函数:\n");
}

// 线程函数
void *SingleInstanceLockNormalLazyPrintHello(void *threadid)
{
    // 主线程与子线程分离，两者相互不干涉，子线程结束同时子线程的资源自动回收
    pthread_detach(pthread_self());

    // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
    int tid = *((int *)threadid);

    printf("Hi, 我是线程 ID[%d]\n", tid);

    // 打印实例地址
    SingleInstanceLockNormalLazy::GetInstance()->Print();

    pthread_exit(NULL);
}