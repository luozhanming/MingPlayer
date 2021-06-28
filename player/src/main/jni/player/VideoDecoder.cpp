//
// Created by 45955 on 2021-06-27.
//

#include "VideoDecoder.h"

VideoDecoder::VideoDecoder(AVFormatContext *formatContext
        , AVCodecContext *codecContext):m_format_context(formatContext),
        m_codec_context(codecContext){
    packets = new SafeQueue<AVPacket*>();
    frames = new SafeQueue<AVFrame*>();
}

VideoDecoder::~VideoDecoder() {

}
