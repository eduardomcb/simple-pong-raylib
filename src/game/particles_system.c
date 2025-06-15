//
// Created by eduardo on 14/06/25.
//
#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include "particles_system.h"
#include "../utils/types.h"
#include "../utils/constants.h"

Particle particles[MAX_PARTICLES];
bool systemActive = false;
float systemTimer = 0.0f;
float systemDuration = 0.0f;
Vector2 targetPosition = {0, 0};

void ActivateParticles(Vector2 target, float duration) {
    targetPosition = target;
    systemActive = true;
    systemTimer = 0.0f;
    systemDuration = duration;

    // Inicializa todas as partículas
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position = target;

        // Velocidade aleatória em todas as direções
        float angle = ((float)rand() / RAND_MAX) * 2.0f * PI;
        float speed = 50.0f + ((float)rand() / RAND_MAX) * 100.0f;
        particles[i].velocity.x = cos(angle) * speed;
        particles[i].velocity.y = sin(angle) * speed;

        particles[i].life = 1.0f + ((float)rand() / RAND_MAX) * 2.0f;

        particles[i].color = WHITE;
    }
}

void UpdateParticles() {
    if (!systemActive) return;

    float deltaTime = GetFrameTime();
    systemTimer += deltaTime;

    // Desativa o sistema após o tempo definido
    if (systemTimer >= systemDuration) {
        systemActive = false;
        return;
    }

    // Atualiza cada partícula
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life <= 0.0f) continue;

        // Move a partícula
        particles[i].position.x += particles[i].velocity.x * deltaTime;
        particles[i].position.y += particles[i].velocity.y * deltaTime;

        // Aplica gravidade
        particles[i].velocity.y += 200.0f * deltaTime;

        // Reduz a vida
        particles[i].life -= deltaTime;

        // Fade out baseado na vida
        float alpha = particles[i].life > 0.0f ? (particles[i].life / 3.0f) * 255 : 0;
        if (alpha > 255) alpha = 255;
        particles[i].color.a = (unsigned char)alpha;
    }
}

void DrawParticles() {
    if (!systemActive) return;

    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life > 0.0f) {
            DrawCircleV(particles[i].position, 3.0f, particles[i].color);
        }
    }
}
