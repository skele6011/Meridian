#include "Level1.hpp"
#include "SDL_render.h"
#include <iostream> // IWYU pragma: keep

Level1::Level1()
    : m_player({100.0f, 100.0f, 24.0f, 36.0f}), m_vel_x(0.0f), m_vel_y(0.0f) {

  // Add somes solids
  m_solids.push_back({0.0f, 900.0f, 1920.0f, 180.0f});
  m_solids.push_back({400.0f, 700.0f, 200.0f, 200.0f});
}

void Level1::update(double fixed_dt, const Input& input) {
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
    std::cout << "Clicking W\n";
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

void Level1::render(Window& window) {
  SDL_SetRenderDrawColor(window.getRenderer(), 137, 180, 250, 255);

  SDL_Rect player_rect = {
      static_cast<int>(m_player.x),
      static_cast<int>(m_player.y),
      static_cast<int>(m_player.width),
      static_cast<int>(m_player.height),
  };
  SDL_RenderFillRect(window.getRenderer(), &player_rect);

  SDL_SetRenderDrawColor(window.getRenderer(), 100, 100, 110, 255);
  for (const auto& solid : m_solids) {
    SDL_Rect solid_rect = {static_cast<int>(solid.x), static_cast<int>(solid.y),
                           static_cast<int>(solid.width),
                           static_cast<int>(solid.height)};
    SDL_RenderFillRect(window.getRenderer(), &solid_rect);
  }
}
