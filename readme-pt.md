<div align="center">
  <img src="logo/icon_simple_pong.png" alt="Simple Pong Logo" width="180" height="180">
  <h1>Simple Pong</h1>
  <p>Um jogo Pong clássico desenvolvido em C usando a biblioteca Raylib, com sistema de partículas, efeitos sonoros e interface.</p>

**[🇧🇷 Português](README-pt.md) | [🇺🇸 English](README.md)**
</div>

<br>

---

## Características

- Jogabilidade clássica de Pong com controles responsivos
- Sistema de partículas para efeitos visuais nas colisões
- Efeitos sonoros para contagem regressiva e colisões
- Sistema de pontuação com tela de vitória
- Função pause/resume
- Contagem regressiva visual antes do início
- Modo debug com informações em tempo real

---

## Como Executar

### Pré-requisitos

- CMake (versão 3.10 ou superior)
- Compilador C (GCC, Clang ou MSVC)
- Raylib (baixada automaticamente)

### Compilação

```bash
git clone https://github.com/eduardomcb/simple-pong-raylib.git
cd simple-pong
mkdir build && cd build
cmake ..
make
./simple_pong
```

---

## Controles

| Ação | Jogador 1 | Jogador 2 |
|------|-----------|-----------|
| Mover para Cima | W | ↑ |
| Mover para Baixo | S | ↓ |
| Iniciar Jogo | SPACE | SPACE |
| Pausar/Despausar | P | P |
| Reiniciar | R | R |
| Debug Info | D (segurar) | D |

---

## Estrutura do Projeto

```
simple-pong/
├── assets/audio/              # Arquivos de som
├── logo/                      # Logo do projeto
├── src/
│   ├── audio/                 # Gerenciamento de áudio
│   ├── game/                  # Lógica principal do jogo
│   │   ├── ball.c/h
│   │   ├── game.c/h
│   │   ├── paddle.c/h
│   │   └── particles_system.c/h
│   ├── utils/                 # Constantes e utilitários
│   └── main.c
└── CMakeLists.txt
```

---

## Tecnologias

- **C** - Linguagem de programação
- **Raylib** - Framework de desenvolvimento de jogos
- **CMake** - Sistema de build

---

## Personalização

Edite `src/utils/constants.h` para modificar configurações do jogo:

```c
#define SCREEN_WIDTH 1280       // Largura da tela
#define SCREEN_HEIGHT 800       // Altura da tela
#define WINNING_SCORE 5         // Pontuação para vitória
#define BALL_INITIAL_SPEED 5    // Velocidade inicial da bola
```
