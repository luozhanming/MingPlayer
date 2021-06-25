//
// Created by Administrator on 2021/6/25.
//

#ifndef MINGPLAYER_MINGPLAYER_H
#define MINGPLAYER_MINGPLAYER_H


class MingPlayer {
private:
    const char *mSource = 0;

public:
    void setDataSource(const char * source);
    void prepare();
    void start();
    void stop();
    void resume();
    void pause();
    long getDuration();
    void seek(int progress);


};


#endif //MINGPLAYER_MINGPLAYER_H
