/*
为线程池做准备并封装线程池
*/
#ifndef ZQWPTHREAD_H
#define ZQWPTHREAD_H
#include "zqwmutex.h"
#include <thread>
namespace Zqw{
class Task{
private:
    void (*_funptr)(void*);
    void *_arg;
    Task *_next_task;
public:
    Task() = delete;
    Task(void (*ptr)(void*), void *arg);
    Task* NextTask();
    void AddNewTask(void (*ptr)(void*), void *arg);
    void RunTask();
    ~Task() = default;
};

class Threadpool
{
private:
    friend void routine(Threadpool *pool); 
    Task *_head;
    Task *_tail;
    Condition *_ready;
    int _used_pthread;
    int _idle_pthread;
    int _max_pthread;
    int _quit;
public:
    Threadpool() = delete;
    Threadpool(int max_pthread);
    void AddTask(void (*fun)(void*), void *arg);
    void Destory();
    ~Threadpool();
};
extern Threadpool pool;
}
#endif