//
// Created by 45955 on 2021-06-26.
//

#ifndef MINGPLAYER_VIDEODECODER_H
#define MINGPLAYER_VIDEODECODER_H

#include <include/ffmpeg/libavutil/frame.h>
#include "SafeQueue.h"

extern "C" {
#include <include/ffmpeg/libavcodec/avcodec.h>
#include <include/ffmpeg/libavformat/avformat.h>
};


class VideoDecoder {
private:
    AVFormatContext *m_format_context = 0;
    AVCodecContext *m_codec_context = 0;



public:
    SafeQueue<AVPacket *> *packets;
    SafeQueue<AVFrame *> *frames;
    VideoDecoder(AVFormatContext *formatContext, AVCodecContext *codecContext);

    ~VideoDecoder();

    void start();

    void stop();

    void release();
};


#endif //MINGPLAYER_VIDEODECODER_H
