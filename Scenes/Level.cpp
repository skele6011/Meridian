#include "Level.hpp"
#include "SDL_render.h"
#include <iostream>

// Everything here is everything that should be in EVERY level, if loading
// images for other levels, do that in those specific levels.
void Level::loadBaseAssets(SDL_Renderer* renderer) {
  std::cout << "Loading base assets..." << std::endl;
  m_player_texture.loadFromFile("../assets/Player-Sheet.png", renderer);
};

void Level::update(double fixed_dt, const Input& input) {
  // 1. Handle input for movement
  float move_speed = 300.0f;
  m_vel_x = 0.0f;
  if (input.isHeld(SDL_SCANCODE_A)) {
    m_vel_x = -move_speed;
  }
  if (input.isHeld(SDL_SCANCODE_D)) {
    m_vel_x = move_speed;
  }
  if (input.isPressed(SDL_SCANCODE_W)) {
    m_vel_y = -500;
  }

  // Simple gravity for testing vertical movement
  float gravity = 900.0f;
  m_vel_y += gravity * static_cast<float>(fixed_dt);

  // X-Axis movement & Collision
  m_player.x += m_vel_x * static_cast<float>(fixed_dt);
  for (const auto& solid : m_solids) {
    if (m_player.intersects(solid)) {
      if (m_vel_x > 0.0f) {
        m_player.x = solid.left() - m_player.width;
      } else if (m_vel_x < 0.0f) {
        m_player.x = solid.right();
      }
    }
  }

  // Y-Axis movement & Collision
  m_player.y += m_vel_y * static_cast<float>(fixed_dt);
  for (const auto& solid : m_solids) {
    if (m_player.intersects(solid)) {
      if (m_vel_y > 0.0f) {
        m_player.y = solid.top() - m_player.height;
        m_vel_y = 0.0f;
      } else if (m_vel_y < 0.0f) {
        m_player.y = solid.bottom();
        m_vel_y = 0.0f;
      }
    }
  }
}

//
void Level::render(Window& window) {
  // Things that will always be rendered happen here first

  // Background
  SDL_SetRenderDrawColor(window.getRenderer(), 137, 180, 250, 255);
  SDL_RenderClear(window.getRenderer());

  // Player
  std::cout << "Rendering player at X: " << m_player.x << " Y: " << m_player.y
            << std::endl;

  // For our test guy, 8x16 each frame, first frame starts at 28 and ends at 36
  SDL_Rect player_src_rect = {28, 0, 8, 16};

  double scale = 5.0;

  m_player.width = 8 * scale;
  m_player.height = 16 * scale;

  m_player_texture.render(window.getRenderer(), static_cast<int>(m_player.x),
                          static_cast<int>(m_player.y), &player_src_rect,
                          scale);
}
