#include "Level.hpp"
#include "SDL_render.h"
#include "SDL_scancode.h"
#include <iostream>

// Everything here is everything that should be in EVERY level, if loading
// images for other levels, do that in those specific levels.
void Level::loadBaseAssets(SDL_Renderer* renderer) {
  std::cout << "Loading base assets..." << std::endl;
  m_player_texture.loadFromFile("../assets/Player-Sheet.png", renderer);
};

void Level::update(double fixed_dt, const Input& input) {
  // Rewind input logic - Might make it so there's an energy bar to use it or
  // smth like when the watch is ready
  if (input.isHeld(SDL_SCANCODE_R) && !m_player_history.empty()) {
    // Pop newest snapshot and restore player to it
    // Popping 1 per frame = 1x speed rewind, pop 2 per frame = 2x speed rewind
    PlayerSnapshot latest = m_player_history.back();
    m_player_history.pop_back();

    m_player.restore(latest);

    // Skip normal update physics so time flows backwards
    return;
  }

  // Record normal timeline
  // Record current state before stepping forward
  m_player_history.push_back(m_player.save());
  if (m_player_history.size() > m_max_history_size) {
    m_player_history.pop_front();
  }

  // Normal player update
  m_player.update(fixed_dt, input, m_solids);
}

//
void Level::render(Window& window) {
  // Things that will always be rendered happen here first

  // Background
  SDL_SetRenderDrawColor(window.getRenderer(), 137, 180, 250, 255);
  SDL_RenderClear(window.getRenderer());

  // Level-specific background
  renderBackground(window);

  // Player
  // std::cout << "Rendering player at X: " << m_player.getX()
  //           << " Y: " << m_player.getY() << std::endl;
  m_player.render(window, m_player_texture);
}
