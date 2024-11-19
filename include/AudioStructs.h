//
// Created by Mohamad on 19/11/2024.
//

#ifndef PONG_AUDIOSTRUCTS_H
#define PONG_AUDIOSTRUCTS_H

#include <string>
#include <utility>

enum class AudioAction{
    PLAY_SOUND,
    STOP_SOUND,
    SET_VOLUME
};

struct AudioMessage{
    AudioAction action;
    std::string soundName;
    float volume;
public:
    AudioMessage() : action(AudioAction::PLAY_SOUND), soundName(""), volume(0.0f) {}
    AudioMessage(AudioAction action, std::string soundName,float volume):action(action),soundName(std::move(soundName)),volume(volume){};
};
#endif //PONG_AUDIOSTRUCTS_H
