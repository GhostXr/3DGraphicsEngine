#include<pthread.h>
#include<iostream>
#include <unistd.h>

using namespace std;

void* say(void*index)
{
    while (true)
    {
        cout<<"hello.."<<&index<<endl;
        
        usleep(2000);
    }
    return NULL;
}

void threadTest()
{
    const int THREAD_NUM = 20;
    pthread_t tids[THREAD_NUM]; //线程的id
    for(int i=0; i<THREAD_NUM; ++i)
    {
        int result = pthread_create(tids+i, nullptr, say, &i);
        if(result != 0)
        {
            cout<<"pthread_create error : "<<result<<endl;
            
        }
    }
    pthread_exit(nullptr);//没有这句的话，当此线程over 的时候，其他线程也over
}
int main11()
{
    threadTest();
    
    return 0;
}
