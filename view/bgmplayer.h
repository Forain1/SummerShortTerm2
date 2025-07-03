#ifndef BGMPLAYER_H
#define BGMPLAYER_H
#include<QMediaPlayer>
#include<QAudioOutput>
class BgmPlayer
{
public:
    BgmPlayer();
    ~BgmPlayer();
    void playBgm();
    void stopBgm();
private:
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
};

#endif // BGMPLAYER_H
