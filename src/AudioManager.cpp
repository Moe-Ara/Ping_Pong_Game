//
// Created by Mohamad on 19/11/2024.
//

#include <iostream>
#include "AudioManager.h"

AudioManager::AudioManager() : running(false) {

}

AudioManager::~AudioManager() {
    stop();
}

void AudioManager::enqueueMessage(const AudioMessage &message) {
    std::lock_guard<std::mutex> lock(queueMutex);
    messageQueue.push(message);
    conditionVariable.notify_one();
}

void AudioManager::loadSound(const std::string &name, const std::string &filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load sound " + filePath);
    }
    soundBuffers[name] = buffer;
    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    sounds[name] = sound;
}

void AudioManager::start() {
    running = true;
    audioThread = std::thread(&AudioManager::proccessMessage, this);

}

void AudioManager::stop() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        running = false;
        conditionVariable.notify_one();
    }
    if (audioThread.joinable()) {
        audioThread.join();
    }
}

void AudioManager::proccessMessage() {
    while (running) {
        AudioMessage message;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            conditionVariable.wait(lock, [this] { return !messageQueue.empty() || !running; });
            if (!running) break;
            message = messageQueue.front();
            messageQueue.pop();
        }

        switch (message.action) {
            case AudioAction::PLAY_SOUND:
                if (sounds.find(message.soundName) != sounds.end()) {
                    sounds[message.soundName].play();
                }
                break;

            case AudioAction::STOP_SOUND:
                if (sounds.find(message.soundName) != sounds.end()) {
                    sounds[message.soundName].stop();
                }
                break;
            case AudioAction::SET_VOLUME:
                if (sounds.find(message.soundName) != sounds.end()) {
                    sounds[message.soundName].setVolume(message.volume);
                }
                break;

        }
    }
}

void AudioManager::playBackgroundMusic(const std::string &filePath, bool loop) {
    if (!backgroundMusic.openFromFile(filePath)) {
        throw std::runtime_error("Failed to load background music: " + filePath);
    }
    backgroundMusic.setLoop(loop);
    backgroundMusic.play();
    backgroundMusicPlaying= true;
}

void AudioManager::stopBackgroundMusic() {
    backgroundMusic.stop();
    backgroundMusicPlaying= false;

}

void AudioManager::setBackgroundMusicVolume(float volume) {
    backgroundMusic.setVolume(volume);
}

AudioManager &AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

bool AudioManager::IsBackgroundMusicPlaying() {
    return backgroundMusicPlaying;
}
