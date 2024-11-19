//
// Created by Mohamad on 19/11/2024.
//

#ifndef PONG_AUDIOMANAGER_H
#define PONG_AUDIOMANAGER_H


#include <string>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "AudioStructs.h"
class AudioManager {
public:
    static AudioManager& getInstance();
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    void enqueueMessage(const AudioMessage& message);
    void loadSound(const std::string& name, const std::string& filePath);
    void start();
    void stop();
    void playBackgroundMusic(const std::string& filePath, bool loop = true);
    void stopBackgroundMusic();
    void setBackgroundMusicVolume(float volume);

    bool IsBackgroundMusicPlaying();

private:
    AudioManager();
    virtual ~AudioManager();

    void proccessMessage();
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;
    sf::Music backgroundMusic;
    std::queue<AudioMessage> messageQueue;
    std::mutex queueMutex;
    std::condition_variable conditionVariable;
    bool running;
    std::thread audioThread;
    bool backgroundMusicPlaying{};
};


#endif //PONG_AUDIOMANAGER_H
