/*
为线程池做准备
*/
#ifndef ZQWMUTEX_H
#define ZQWMUTEX_H
#include<pthread.h>
namespace Zqw
{
    class Condition{
        private:
            pthread_mutex_t _mutex;
            pthread_cond_t _cond;
        public:
            Condition();
            int ConditionLock();
            int ConditionUnlock();
            int ConditionWait();
            int ConditionSignal();
            int ConditionBroadcast();
            ~Condition();
    };
}
#endif