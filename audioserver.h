#ifndef AUDIOSERVER_H
#define AUDIOSERVER_H

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.hh>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

class AudioServer {
public:
    static AudioServer& getInstance();

    void playSound(const char* filename);

    // Забороняємо копіювання
    AudioServer(const AudioServer&) = delete;
    AudioServer& operator=(const AudioServer&) = delete;

private:
    AudioServer();
    ~AudioServer();

    void checkAlErrors();
    std::vector<ALshort> loadWavFile(const char* filename, ALsizei* sampleRate, ALenum* format);
    void playSoundInternal(ALuint buffer);

    ALCdevice* device;
    ALCcontext* context;
};

#endif // AUDIOSERVER_H
