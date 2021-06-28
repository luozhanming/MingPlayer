//
// Created by Administrator on 2021/6/25.
//

#ifndef MINGPLAYER_MINGPLAYER_H
#define MINGPLAYER_MINGPLAYER_H


#include <stdint.h>
#include <include/ffmpeg/libavformat/avformat.h>
#include "string"
#include "JniCallbackHelper.h"
#include "AVSynchronizer.h"
#include "pthread.h"

class MingPlayer {
private:
    JniCallbackHelper *m_callback_helper = 0;
    std::string source;
    AVSynchronizer *synchronizer = 0;
    AVFormatContext *m_format = 0;
    pthread_t prepare_task;



public:
    typedef void(*VideoOutputCallback) (uint8_t *data, int, int, int); // 函数指针声明定义
    void setDataSource(const char * source);
    void prepare();
    void start();
    void stop();
    void resume();
    void pause();
    long getDuration();
    void seek(int progress);

    void _prepare();

    void setJNICallbackHelper(JniCallbackHelper *helper);


};


#endif //MINGPLAYER_MINGPLAYER_H
