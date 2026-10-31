#include "Player.hpp"
#include "SDL_scancode.h"

Player::Player(float start_x, float start_y, float width, float height)
    : m_bounds{start_x, start_y, width, height}, m_vx(0.0f), m_vy(0.0f),
      m_frame_width(8), m_frame_height(16), m_scale(5.0f),
      m_is_grounded(false) {
  m_bounds.width = m_bounds.width * m_scale;
  m_bounds.height = m_bounds.height * m_scale;
}

void Player::update(double dt, const Input& input,
                    const std::vector<Rect>& solids) {
  float dt_f = static_cast<float>(dt); // Because Rect using floats

  // 1. Horizontal input
  float move_speed = 300.0f;
  m_vx = 0.0f;

  if (input.isHeld(SDL_SCANCODE_A)) {
    m_vx = -move_speed;
  }
  if (input.isHeld(SDL_SCANCODE_D)) {
    m_vx = move_speed;
  }

  // 2. Handle jump input (Should add buffer time)
  if (input.isPressed(SDL_SCANCODE_W) && m_is_grounded) {
    m_vy = -500.0f;
    m_is_grounded = false;
  }

  // 3. Gravity
  float gravity = 900.0f;
  m_vy += gravity * dt_f;

  // 4. X-Axis movement & Collision
  m_bounds.x += m_vx * dt_f;
  for (const auto& solid : solids) {
    if (m_bounds.intersects(solid)) {
      if (m_vx > 0.0f) {
        m_bounds.x = solid.left() - m_bounds.width;
      } else if (m_vx < 0.0f) {
        m_bounds.x = solid.right();
      }
    }
  }

  // 5. Y-Axis movement & Collision
  m_bounds.y += m_vy * dt_f;
  m_is_grounded = false; // Reset ground status before checking floor contact

  for (const auto& solid : solids) {
    if (m_bounds.intersects(solid)) {
      if (m_vy > 0.0f) {
        m_bounds.y = solid.top() - m_bounds.height;
        m_vy = 0.0f;
        m_is_grounded = true;
      } else if (m_vy < 0.0f) {
        m_bounds.y = solid.bottom();
        m_vy = 0.0f;
      }
    }
  }
}

void Player::render(Window& window, Texture& spriteSheet) {
  // Hardcoded for now (8x16 starting at x = 28)
  SDL_Rect player_src_rect = {28, 0, m_frame_width, m_frame_height};

  spriteSheet.render(window.getRenderer(), static_cast<int>(m_bounds.x),
                     static_cast<int>(m_bounds.y), &player_src_rect, m_scale);
}

Rect Player::getBoundingBox() const { return m_bounds; }
