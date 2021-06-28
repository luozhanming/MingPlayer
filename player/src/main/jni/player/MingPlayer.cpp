//
// Created by Administrator on 2021/6/25.
//

#include <include/ffmpeg/libavutil/dict.h>
#include <include/ffmpeg/libavcodec/avcodec.h>
#include <include/ffmpeg/libavutil/avutil.h>
#include "MingPlayer.h"
#include "utils.h"
#include "include/ffmpeg/libavformat/avformat.h"


void *run_prepare(void *arg) {
    auto *player = static_cast<MingPlayer *>(arg);
    player->_prepare();
    return nullptr;
}

void MingPlayer::prepare() {
    //1.判断source是否为空
    //2.解封装
    //3.找出音频视频通道
    if (!source.empty()) {
        LOGE("No source has been set.");
        return;
    }
    avformat_network_init();
    pthread_create(&prepare_task, 0, run_prepare, this);


}

void MingPlayer::setJNICallbackHelper(JniCallbackHelper *helper) {
    this->m_callback_helper = helper;
}

void MingPlayer::setDataSource(const char *source) {
    this->source = source;
}

void MingPlayer::_prepare() {
    m_format = avformat_alloc_context();
    int ret = 0;
    AVDictionary * dict = 0;
    av_dict_set(&dict, "timeout", "5000000", 0);
    ret = avformat_open_input(&m_format, source.data(), 0, &dict);
    if (!ret) {
        LOGE("Source %s open failed.", source.data());
        this->m_callback_helper->onError(THREAD_CHILD, FFMPEG_CAN_NOT_OPEN_URL);
        avformat_close_input(&m_format);
        avformat_free_context(m_format);
        return;
    }
    ret = avformat_find_stream_info(m_format, &dict);
    if (!ret) {
        LOGE("Source %s open failed.", source.data());
        this->m_callback_helper->onError(THREAD_CHILD, FFMPEG_CAN_NOT_FIND_STREAMS);
        avformat_close_input(&m_format);
        avformat_free_context(m_format);
        return;
    }
    int streamNum = m_format->nb_streams;
    synchronizer = new AVSynchronizer();

    for (int i = 0; i < streamNum; i++) {
        AVStream *stream = m_format->streams[i];
        AVCodecParameters *codepar = stream->codecpar;
        AVCodec *codec = avcodec_find_decoder(codepar->codec_id);
        if (!codec) {
            // TODO 第二节课新增
            if (m_callback_helper) {
                m_callback_helper->onError(THREAD_CHILD, FFMPEG_FIND_DECODER_FAIL);
            }
            // TODO 播放器收尾 1
            avformat_close_input(&m_format);
        }
        AVCodecContext *codecContext = avcodec_alloc_context3(codec);
        if (!codecContext) {
            if (m_callback_helper) {
                m_callback_helper->onError(THREAD_CHILD, FFMPEG_ALLOC_CODEC_CONTEXT_FAIL);
            }

            // TODO 播放器收尾 1
            avcodec_free_context(&codecContext); // 释放此上下文 avcodec 他会考虑到，你不用管*codec
            avformat_close_input(&m_format);

            return;
        }
        ret = avcodec_parameters_to_context(codecContext, codepar);
        if (ret < 0) {
            // TODO 第二节课新增
            if (m_callback_helper) {
                m_callback_helper->onError(THREAD_CHILD, FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL);
            }
            // TODO 播放器收尾 1
            avcodec_free_context(&codecContext); // 释放此上下文 avcodec 他会考虑到，你不用管*codec
            avformat_close_input(&m_format);
            return;
        }
        /**
         * TODO 第九步：打开解码器
         */
        ret = avcodec_open2(codecContext, codec, nullptr);
        if (ret) { // 非0就是true
            // TODO 第二节课新增
            if (m_callback_helper) {
                m_callback_helper->onError(THREAD_CHILD, FFMPEG_OPEN_DECODER_FAIL);
            }
            // TODO 播放器收尾 1
            avcodec_free_context(&codecContext); // 释放此上下文 avcodec 他会考虑到，你不用管*codec
            avformat_close_input(&m_format);
            return;
        }
        if (codepar->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO) {
            VideoDecoder *decoder = new VideoDecoder(m_format,codecContext);
            synchronizer->setVideoDecoder(decoder);
        } else if (codepar->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO) {

        } else {

        }
    }
}
