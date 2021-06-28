//
// Created by 45955 on 2021-06-26.
//

#include "AVSynchronizer.h"


void *playtask(void *arg) {
    auto *synchronizer = static_cast<AVSynchronizer *>(arg);
    synchronizer->runPlay();
    return nullptr; // 必须返回，坑，错误很难找
}

void AVSynchronizer::start() {
    //1.开启音频视频解码
    //2.创建线程不断从音频获取帧
}

void AVSynchronizer::runPlay() {
    while (isStarting) {
        if (!isPausing) {

        }
    }
}
