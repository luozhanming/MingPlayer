//
// Created by 45955 on 2021-06-26.
//

#ifndef MINGPLAYER_AVSYNCHRONIZER_H
#define MINGPLAYER_AVSYNCHRONIZER_H


#include "VideoDecoder.h"
#include "AudioDecoder.h"
#include "pthread.h"

class AVSynchronizer {
private:
    bool isStarting = false;
    bool isPausing = false;
    VideoDecoder *video_decoder = 0;
    AudioDecoder *audio_decoder = 0;
    pthread_t play_task;     //播放线程





public:
    void runPlay();
    void setVideoDecoder(VideoDecoder *decoder);
    void setAudioDecoder(AudioDecoder *Decoder);
    void start();
    void stop();
    void resume();
    void pause();

};


#endif //MINGPLAYER_AVSYNCHRONIZER_H
