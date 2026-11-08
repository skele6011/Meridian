#include "Level.hpp"
#include "SDL_render.h"
#include "SDL_scancode.h"

#include <algorithm>
#include <iostream>

// Everything here is everything that should be in EVERY level, if loading
// images for other levels, do that in those specific levels.
void Level::loadBaseAssets(SDL_Renderer* renderer) {
  std::cout << "Loading base assets..." << std::endl;
  m_player_texture.loadFromFile("../assets/Player-Sheet.png", renderer);

  // Load tileset here for now
  m_tileset_texture.loadFromFile("../assets/tiles.png", renderer);
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
    updateCamera();
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
  updateCamera();
}

//
void Level::render(Window& window) {
  // Things that will always be rendered happen here first

  // Background
  SDL_SetRenderDrawColor(window.getRenderer(), 137, 180, 250, 255);
  SDL_RenderClear(window.getRenderer());

  // Tile visuals
  for (const auto& tile : m_tiles) {
    m_tileset_texture.renderEx(
        window.getRenderer(), tile.x - static_cast<int>(m_camera_x),
        tile.y - static_cast<int>(m_camera_y), &tile.src_rect, 1.0f,
        static_cast<SDL_RendererFlip>(tile.flip));
  }

  // Player
  // std::cout << "Rendering player at X: " << m_player.getX()
  //           << " Y: " << m_player.getY() << std::endl;
  m_player.render(window, m_player_texture, m_camera_x, m_camera_y);
}

void Level::updateCamera() {
  const float screen_w = 320.0f;
  const float screen_h = 180.0f;

  // Center on the player (+ half the player's size so it's the middle, not the
  // left edge)
  m_camera_x = m_player.getX() + 4.0f - screen_w / 2.0f;
  m_camera_y = m_player.getY() + 8.0f - screen_h / 2.0f;

  // Clamp so we never show outside the map
  float max_x = static_cast<float>(m_level_width) - screen_w;
  float max_y = static_cast<float>(m_level_height) - screen_h;
  m_camera_x = std::clamp(m_camera_x, 0.0f, max_x);
  m_camera_y = std::clamp(m_camera_y, 0.0f, max_y);
}
