//
// Created by 45955 on 2021-06-27.
//

#ifndef MINGPLAYER_JNICALLBACKHELPER_H
#define MINGPLAYER_JNICALLBACKHELPER_H
#include <jni.h>


class JniCallbackHelper {
private:
    JavaVM *vm = 0;
    JNIEnv *env = 0;
    jobject job;
    jmethodID jmd_prepared;
    jmethodID jmd_onError;
    jmethodID jmd_onProgress; // 播放音频的时间搓回调

public:
    JniCallbackHelper(JavaVM *vm, JNIEnv *env, jobject job);
    ~JniCallbackHelper();

    void onPrepared(int thread_mode);
    void onError(int thread_mode, int error_code);

    void onProgress(int thread_mode, int audio_time);

};


#endif //MINGPLAYER_JNICALLBACKHELPER_H
