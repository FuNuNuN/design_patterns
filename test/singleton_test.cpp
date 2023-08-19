#include "singleton/singleton_instance_normal_lazy.h"
#include "singleton/singleton_instance_lock_normal_lazy.h"
#include "singleton/singleton_instance_local_lazy.h"
#include "singleton/singleton_instance_hungry.h"
#include <iostream>
#include "gtest/gtest.h"
#include <pthread.h>  // pthread_create

#define NUM_THREADS 5 // 线程个数

class SingleInstanceTest : public testing::Test {
protected:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};

TEST_F(SingleInstanceTest, NormalLazyTest)
{
    pthread_t threads[NUM_THREADS] = {0};
    int indexes[NUM_THREADS] = {0}; // 用数组来保存i的值

    int ret = 0;
    int i = 0;

    printf("main() : 开始 ... \n");

    for (i = 0; i < NUM_THREADS; i++) {
        printf("main() : 创建线程[%d]\n", i);

        indexes[i] = i; // 先保存i的值

        // 传入的时候必须强制转换为void* 类型，即无类型指针
        ret = pthread_create(&threads[i], NULL, SingleInstanceNormalLazyPrintHello, (void *)&(indexes[i]));
        if (ret) {
            printf("Error:无法创建线程,ret = %d\n", ret);
            exit(-1);
        }
    }
    sleep(6);
    // 手动释放单实例的资源
    SingleInstanceNormalLazy::deleteInstance();
    printf("main() : 结束! \n");

    EXPECT_EQ(0, 0);
}

TEST_F(SingleInstanceTest, LockNormalLazyTest)
{
    pthread_t threads[NUM_THREADS] = {0};
    int indexes[NUM_THREADS] = {0}; // 用数组来保存i的值

    int ret = 0;
    int i = 0;

    printf("main() : 开始 ... \n");

    for (i = 0; i < NUM_THREADS; i++) {
        printf("main() : 创建线程[%d]\n", i);

        indexes[i] = i; // 先保存i的值

        // 传入的时候必须强制转换为void* 类型，即无类型指针
        ret = pthread_create(&threads[i], NULL, SingleInstanceLockNormalLazyPrintHello, (void *)&(indexes[i]));
        if (ret) {
            printf("Error:无法创建线程,ret = %d\n", ret);
            exit(-1);
        }
    }
    sleep(6);
    // 手动释放单实例的资源
    SingleInstanceLockNormalLazy::deleteInstance();
    printf("main() : 结束! \n");

    EXPECT_EQ(0, 0);
}

TEST_F(SingleInstanceTest, LocalLazyTest)
{
    pthread_t threads[NUM_THREADS] = {0};
    int indexes[NUM_THREADS] = {0}; // 用数组来保存i的值

    int ret = 0;
    int i = 0;

    printf("main() : 开始 ... \n");

    for (i = 0; i < NUM_THREADS; i++) {
        printf("main() : 创建线程[%d]\n", i);

        indexes[i] = i; // 先保存i的值

        // 传入的时候必须强制转换为void* 类型，即无类型指针
        ret = pthread_create(&threads[i], NULL, SingleInstanceLocalLazyPrintHello, (void *)&(indexes[i]));
        if (ret) {
            printf("Error:无法创建线程,ret = %d\n", ret);
            exit(-1);
        }
    }
    sleep(6);
    printf("main() : 结束! \n");

    EXPECT_EQ(0, 0);
}

TEST_F(SingleInstanceTest, HungryTest)
{
    pthread_t threads[NUM_THREADS] = {0};
    int indexes[NUM_THREADS] = {0}; // 用数组来保存i的值

    int ret = 0;
    int i = 0;

    printf("main() : 开始 ... \n");

    for (i = 0; i < NUM_THREADS; i++) {
        printf("main() : 创建线程[%d]\n", i);

        indexes[i] = i; // 先保存i的值

        // 传入的时候必须强制转换为void* 类型，即无类型指针
        ret = pthread_create(&threads[i], NULL, SingleInstanceHungryPrintHello, (void *)&(indexes[i]));
        if (ret) {
            printf("Error:无法创建线程,ret = %d\n", ret);
            exit(-1);
        }
    }
    sleep(6);
    // 手动释放单实例的资源
    SingleInstanceHungry::deleteInstance();
    printf("main() : 结束! \n");

    EXPECT_EQ(0, 0);
}