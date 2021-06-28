#include <jni.h>
#include <player/MingPlayer.h>
#include <player/utils.h>

//
// Created by Administrator on 2021/6/25.
//


JavaVM *vm=0;
MingPlayer *player = 0;


jint JNI_OnLoad(JavaVM * vm, void * args) {
    ::vm = vm;
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_luozhanming_player_MingPlayer_setDataSourceNative(JNIEnv *env, jobject thiz,
                                                          jstring source) {
    if(!player){
        player = new MingPlayer();
    }
    const char*src = env->GetStringUTFChars(source,0);
    player->setDataSource(src);
    env->ReleaseStringUTFChars(source,src);
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_luozhanming_player_MingPlayer_prepareNative(JNIEnv *env, jobject thiz) {
    if(!player){
        LOGE("未设置视频源地址");
        return;
    }
}