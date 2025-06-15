//
// Created by eduardo on 14/06/25.
//

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
#include "raylib.h"

// Identificadores dos audios para referencia
typedef enum {
    AUDIO_COUNTDOWN = 0,
    AUDIO_PADDLE_HIT,
    // AUDIO_SCORE,
    AUDIO_COUNT  // Manter para representar o total de audios
} AudioId;

// Funções o gerenciador de audio
void InitAudioManager();
void CleanupAudioManager(void);
void PlayAudio(AudioId audioId);
void PlayAudioWithVolume(AudioId audioId, float volume);
bool IsAudioPlaying(AudioId audioId);
bool IsAudioLoaded(AudioId audioId);


#endif //AUDIO_MANAGER_H
