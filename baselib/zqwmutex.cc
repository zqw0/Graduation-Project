#include"zqwmutex.h"
namespace Zqw{
    Condition::Condition(){
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond, nullptr);
    }
    int Condition::ConditionLock(){
        return pthread_mutex_lock(&_mutex);
    }
    int Condition::ConditionUnlock(){
        return pthread_mutex_unlock(&_mutex);
    }
    int Condition::ConditionWait(){
        return pthread_cond_wait(&_cond, &_mutex);
    }
    int Condition::ConditionSignal(){
        return pthread_cond_signal(&_cond);
    }
    int Condition::ConditionBroadcast(){
        return pthread_cond_broadcast(&_cond);
    }
    Condition::~Condition(){
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }
}