//
// Created by 45955 on 2021-06-27.
//

#ifndef MINGPLAYER_SAFEQUEUE_H
#define MINGPLAYER_SAFEQUEUE_H

#include "pthread.h"
#include "queue"

using namespace std;

template<typename T>
class SafeQueue {

public:
    typedef void (*ReleaseCallback)(T *); // 函数指针定义 做回调 用来释放T里面的内容的

private:
    queue<T> queue;
    pthread_mutex_t mutex; // 互斥锁 安全
    pthread_cond_t cond; // 等待 和 唤醒
    int work; // 标记队列是否工作
    ReleaseCallback releaseCallback;

public:


    SafeQueue();

    ~SafeQueue();

    void insertToQueue(T value);

    int getQueueAndDel(T &value);

    void setWork(int work);

    bool empty();

    int size();

    void clear();

    void setReleaseCallback(ReleaseCallback callback);


};

template<typename T>
SafeQueue<T>::SafeQueue() {
    pthread_mutex_init(&mutex, 0); // 初始化互斥锁  动态初始化锁
    pthread_cond_init(&cond, 0); // 初始化条件变量
}

template<typename T>
SafeQueue<T>::~SafeQueue() {
    pthread_mutex_destroy(&mutex); // 释放互斥锁
    pthread_cond_destroy(&cond); // 释放条件变量
}

template<typename T>
void SafeQueue<T>::insertToQueue(T value) {
    pthread_mutex_lock(&mutex); // 多线程的访问（先锁住）

    if (work) {
        // 工作状态
        queue.push(value);
        pthread_cond_signal(&cond); // 当插入数据包 进队列后，要发出通知唤醒
    } else {
        //非工作状态，释放value，不知道如何释放， T类型不明确，我没有办法释放（让外界释放）
        if (releaseCallback) {
            releaseCallback(&value); // 让外界释放我们的 value
        }
    }

    pthread_mutex_unlock(&mutex); // 多线程的访问（要解锁）
}

template<typename T>
int SafeQueue<T>::getQueueAndDel(T &value) {
    int ret = 0; // 默认是false

    pthread_mutex_lock(&mutex); // 多线程的访问（先锁住）

    while (work && queue.empty()) {
        // 如果是工作专题 并且 队列里面没有数据，我就阻塞这这里睡觉
        pthread_cond_wait(&cond, &mutex); // 没有数据就睡觉（C++线程的内容）
    }

    if (!queue.empty()) { // 如果队列里面有数据，就进入此if
        // 取出队列的数据包 给外界，并删除队列数据包
        value = queue.front();
        queue.pop(); // 删除队列中的数据
        ret = 1; // 成功了 Success 放回值  true
    }

    pthread_mutex_unlock(&mutex); // 多线程的访问（要解锁）

    return ret;
}

template<typename T>
void SafeQueue<T>::setWork(int work) {
    pthread_mutex_lock(&mutex); // 多线程的访问（先锁住）

    this->work = work;

    // 每次设置状态后，就去唤醒下，有没有阻塞睡觉的地方
    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&mutex); // 多线程的访问（要解锁）
}

template<typename T>
bool SafeQueue<T>::empty() {
    return queue.empty();
}

template<typename T>
int SafeQueue<T>::size() {
    return queue.size();
}

template<typename T>
void SafeQueue<T>::clear() {
    pthread_mutex_lock(&mutex); // 多线程的访问（先锁住）

    unsigned int size = queue.size();

    for (int i = 0; i < size; ++i) {
        //循环释放队列中的数据
        T value = queue.front();
        if(releaseCallback){
            releaseCallback(&value); // 让外界去释放堆区空间
        }
        queue.pop(); // 删除队列中的数据，让队列为0
    }

    pthread_mutex_unlock(&mutex); // 多线程的访问（要解锁）
}

template<typename T>
void SafeQueue<T>::setReleaseCallback(SafeQueue::ReleaseCallback callback) {
    this->releaseCallback = releaseCallback;
}


#endif //MINGPLAYER_SAFEQUEUE_H
