#include "Level1.hpp"
#include <iostream>

Level1::Level1()
    : m_player_x(100.0f), m_player_y(100.0f), m_player_width(50.0f),
      m_player_height(50.0f), m_player_speed(300.0f) {}

void Level1::update(double fixed_dt, const Input& input) {
  // Basic movement based on input and fixed_dt for deterministic speed
  if (input.isHeld(SDL_SCANCODE_W) || input.isHeld(SDL_SCANCODE_UP)) {
    m_player_y -= m_player_speed * static_cast<float>(fixed_dt);
  }
  if (input.isHeld(SDL_SCANCODE_S) || input.isHeld(SDL_SCANCODE_DOWN)) {
    m_player_y += m_player_speed * static_cast<float>(fixed_dt);
  }
  if (input.isHeld(SDL_SCANCODE_A) || input.isHeld(SDL_SCANCODE_LEFT)) {
    m_player_x -= m_player_speed * static_cast<float>(fixed_dt);
  }
  if (input.isHeld(SDL_SCANCODE_D) || input.isHeld(SDL_SCANCODE_RIGHT)) {
    m_player_x += m_player_speed * static_cast<float>(fixed_dt);
  }
}

void Level1::render(Window& window) {
  SDL_SetRenderDrawColor(window.getRenderer(), 137, 180, 250, 255);

  SDL_Rect player_rect = {
      static_cast<int>(m_player_x),
      static_cast<int>(m_player_y),
      static_cast<int>(m_player_width),
      static_cast<int>(m_player_height),
  };

  SDL_RenderFillRect(window.getRenderer(), &player_rect);
}
