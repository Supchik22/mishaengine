#include "audioserver.h"

AudioServer& AudioServer::getInstance() {
    static AudioServer instance;
    return instance;
}

AudioServer::AudioServer() {
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Failed to open OpenAL device" << std::endl;
        exit(1);
    }

    context = alcCreateContext(device, nullptr);
    if (!alcMakeContextCurrent(context)) {
        std::cerr << "Failed to set OpenAL context" << std::endl;
        exit(1);
    }

    checkAlErrors();
}

AudioServer::~AudioServer() {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void AudioServer::checkAlErrors() {
    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        std::cerr << "OpenAL error: " << alGetString(error) << std::endl;
        exit(1);
    }
}

std::vector<ALshort> AudioServer::loadWavFile(const char* filename, ALsizei* sampleRate, ALenum* format) {
    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(filename, SFM_READ, &sfInfo);
    if (!sndFile) {
        std::cerr << "Failed to open sound file: " << filename << std::endl;
        exit(1);
    }

    if (sfInfo.channels == 1) {
        *format = AL_FORMAT_MONO16;
    } else if (sfInfo.channels == 2) {
        *format = AL_FORMAT_STEREO16;
    } else {
        std::cerr << "Unsupported channel count: " << sfInfo.channels << std::endl;
        sf_close(sndFile);
        exit(1);
    }

    std::vector<ALshort> samples(sfInfo.frames * sfInfo.channels);
    sf_read_short(sndFile, samples.data(), samples.size());
    sf_close(sndFile);

    *sampleRate = sfInfo.samplerate;
    return samples;
}

void AudioServer::playSound(const char* filename) {
    ALsizei sampleRate;
    ALenum format;
    std::vector<ALshort> samples = loadWavFile(filename, &sampleRate, &format);

    ALuint buffer;
    alGenBuffers(1, &buffer);
    checkAlErrors();
    alBufferData(buffer, format, samples.data(), samples.size() * sizeof(ALshort), sampleRate);
    checkAlErrors();

    std::thread playThread(&AudioServer::playSoundInternal, this, buffer);
    playThread.detach(); // Запуск потоку у фоновому режимі
}

void AudioServer::playSoundInternal(ALuint buffer) {
    ALuint source;
    alGenSources(1, &source);
    checkAlErrors();
    alSourcei(source, AL_BUFFER, buffer);
    checkAlErrors();

    alSourcePlay(source);
    checkAlErrors();

    // Очікуємо, поки звук не завершиться
    ALint state;
    do {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (state == AL_PLAYING);

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
}
