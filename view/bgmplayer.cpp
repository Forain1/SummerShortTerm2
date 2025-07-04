#include "bgmplayer.h"

BgmPlayer::BgmPlayer() {
    player = new QMediaPlayer();
    audioOutput = new QAudioOutput();

    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/src/music/battle0.mp3"));
    audioOutput->setVolume(0);
}

BgmPlayer::~BgmPlayer(){
    delete player;
    delete audioOutput;
}

void BgmPlayer::playBgm(){
    player->play();
}

void BgmPlayer::stopBgm(){
    player->stop();
}

void BgmPlayer::setVolume(int v){
    auto newV = v/100.0;
    audioOutput->setVolume(newV);
}
