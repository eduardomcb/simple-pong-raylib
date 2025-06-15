//
// Created by eduardo on 13/06/25.
//
#include "raylib.h"
#include "audio/audio_manager.h"
#include "game/game.h"
#include "utils/constants.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    InitAudioManager();

    SetTargetFPS(TARGET_FPS);

    GameState game;
    InitGame(&game);

    static int lastCountdownNumber = 0;

    while (!WindowShouldClose()) {
        UpdateGame(&game);

        if (game.currentScreen == GAME_COUNTDOWN &&
            game.countdownNumber != lastCountdownNumber &&
            game.countdownNumber > 0 && !IsAudioPlaying(AUDIO_COUNTDOWN)) {
            PlayAudio(AUDIO_COUNTDOWN);
            TraceLog(LOG_DEBUG, "Tocando audio de contagem");
            lastCountdownNumber = game.countdownNumber;
            }

        // redefinir som
        if (game.currentScreen != GAME_COUNTDOWN) {
            lastCountdownNumber = 0;
        }
        DrawGame(&game);
    }

    CleanupAudioManager();
    CloseWindow();

    return 0;
}
