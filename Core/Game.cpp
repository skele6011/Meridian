#include "Game.hpp"
#include <SDL.h>

Game::Game() : m_window("Meridian", 1920, 1080), m_is_running(true) {}

void Game::run() {
  if (!m_window.isOpen()) {
    return;
  }

  const double FIXED_DT =
      1.0 / 120.0; // Might change later or allow for adjusting
  double accumulator = 0.0;

  Uint64 last_counter = SDL_GetPerformanceCounter();
  double frequency = static_cast<double>(SDL_GetPerformanceFrequency());

  while (m_window.isOpen() && m_is_running) {
    // 1. Handle OS window events & input
    m_window.handleWindowEvents();
    m_input.update();

    if (m_input.isPressed(SDL_SCANCODE_ESCAPE)) {
      // TODO Make a confirmation screen
      m_is_running = false;
    }

    // 2. Delta time calculation
    Uint64 current_counter = SDL_GetPerformanceCounter();
    double frame_time =
        static_cast<double>(current_counter - last_counter) / frequency;
    last_counter = current_counter;

    if (frame_time > 0.25) {
      frame_time = 0.25; // Prevent spiral of death on lag spikes
    }

    accumulator += frame_time;

    // 3. Fixed-timestep updates (120 Hz)
    while (accumulator >= FIXED_DT) {
      // TODO: Update game logic / active level here using FIXED_DT
      accumulator -= FIXED_DT;
    }

    // 4. Render
    m_window.clear();

    // TODO: Render active level here

    m_window.render();
  }
}
