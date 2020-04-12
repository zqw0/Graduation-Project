#include "zqwpthread.h"
namespace Zqw{
    Task::Task(void (*ptr)(void*), void *arg){
        _funptr = ptr;
        _arg = arg;
        _next_task = nullptr;
    }
    Task* Task::NextTask(){
        return _next_task;
    }
    void Task::AddNewTask(void (*ptr)(void*), void *arg){
        _next_task = new Task(ptr, arg);
    }
    void Task::RunTask(){
        _funptr(_arg);
    }
    Threadpool::Threadpool(int max_pthread){
        _head = nullptr;
        _tail = nullptr;
        _ready = new Condition;
        _used_pthread = 0;
        _idle_pthread = 0;
        _max_pthread = max_pthread;
        _quit = 0;
    }
    void routine(Threadpool *pool){
        while (1){
            pool->_ready->ConditionLock();
            pool->_idle_pthread++;
            while(pool->_head == nullptr && !pool->_quit)
                pool->_ready->ConditionWait();
            if(pool->_head != nullptr){
                pool->_idle_pthread--;
                Task *now = pool->_head;
                pool->_head = now->NextTask();
                pool->_ready->ConditionUnlock();
                now->RunTask();
                pool->_ready->ConditionLock();
            }
            if(pool->_head == nullptr && pool->_quit){
                pool->_used_pthread--;
                if(!pool->_used_pthread)
                    pool->_ready->ConditionSignal();
                pool->_ready->ConditionUnlock();
                break;
            }
            pool->_ready->ConditionUnlock();
        }
        return;
    }
    void Threadpool::AddTask(void (*fun)(void*), void *arg){
        _ready->ConditionLock();
        if(_head == nullptr){
            _head = new Task(fun, arg);
            _tail = _head;
        }else{
            _tail->AddNewTask(fun, arg);
            _tail = _tail->NextTask();
        }
        if(_idle_pthread && _used_pthread == _max_pthread)
            _ready->ConditionSignal();
        if(_used_pthread < _max_pthread){
            _used_pthread++;
            std::thread t(routine, this);
            t.detach();
        }
        _ready->ConditionUnlock();
    }
    void Threadpool::Destory(){
        _ready->ConditionLock();
        if(!_used_pthread)
            return;
        if(_used_pthread){
            _quit = 1;
            if(_idle_pthread)
                _ready->ConditionBroadcast();
            while(_used_pthread)
                _ready->ConditionWait();
        }
        _ready->ConditionUnlock();
        delete _ready;
    }
    Threadpool::~Threadpool(){
        Destory();
    }
    Threadpool pool(10);
}








