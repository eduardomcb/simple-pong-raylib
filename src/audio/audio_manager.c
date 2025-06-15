//
// Created by eduardo on 14/06/25.
//
#include "audio_manager.h"

static const char* audioFiles[AUDIO_COUNT] = {
    "assets/audio/countdown.mp3",
    "assets/audio/paddle_hit.mp3",
    // "assets/audio/score.mp3",
};

// Armazenamento de audios
static Sound sounds[AUDIO_COUNT];
static bool audioLoaded[AUDIO_COUNT];
static float masterVolume = 1.0f;
static bool audioInitialized = false;

void InitAudioManager() {
    if (audioInitialized) return;

    InitAudioDevice();

    // Inicializar arrays
    for (int i = 0; i < AUDIO_COUNT; i++) {
        audioLoaded[i] = false;
    }

    // Carregar todos arquivos de audio
    for (int i = 0; i < AUDIO_COUNT; i++) {
        if (FileExists(audioFiles[i])) {
            sounds[i] = LoadSound(audioFiles[i]);
            audioLoaded[i] = true;
            TraceLog(LOG_INFO, "Audio carregado: %s\n", audioFiles[i]);
        } else {
            TraceLog(LOG_INFO,"Arquivo de audio não encontrado: %s\n", audioFiles[i]);
            audioLoaded[i] = false;
        }
    }

    audioInitialized = true;
    TraceLog(LOG_INFO,"Gerenciador de audio inicializado\n");
}

void CleanupAudioManager(void) {
    if (!audioInitialized) return;

    // Descarrega todos os audios
    for (int i = 0; i < AUDIO_COUNT; i++) {
        if (audioLoaded[i]) {
            UnloadSound(sounds[i]);
            audioLoaded[i] = false;
        }
    }

    CloseAudioDevice();
    audioInitialized = false;
    TraceLog(LOG_INFO,"Gerenciador de audio limpinho\n");
}

void PlayAudio(AudioId audioId) {
    PlayAudioWithVolume(audioId, masterVolume);
}

void PlayAudioWithVolume(AudioId audioId, float volume) {
    if (!audioInitialized) {
        TraceLog(LOG_INFO,"Não foi possivel inicializar o gerenciador de audios\n");
        return;
    }

    if (audioId >= AUDIO_COUNT) {
        TraceLog(LOG_INFO, "ID de audio invalido: %d\n", audioId);
        return;
    }

    if (!audioLoaded[audioId]) {
        TraceLog(LOG_INFO,"Audio não foi carregado com esse ID: %d\n", audioId);
        return;
    }

    SetSoundVolume(sounds[audioId], volume);
    PlaySound(sounds[audioId]);
}

bool IsAudioPlaying(AudioId audioId) {
    return IsSoundPlaying(sounds[audioId]);
}

bool IsAudioLoaded(AudioId audioId) {
    if (audioId >= AUDIO_COUNT) return false;
    return audioLoaded[audioId];
}
