#include "Player.hpp"
#include "SDL_render.h"
#include "SDL_scancode.h"

Player::Player(float start_x, float start_y, float width, float height)
    : m_bounds{start_x, start_y, width, height}, m_vx(0.0f), m_vy(0.0f),
      m_frame_width(8), m_frame_height(16), m_scale(1.0f), m_is_grounded(false),
      m_current_state(PlayerState::Idle), m_previous_state(PlayerState::Idle),
      m_facing_right(true) {

  // Initialize state animations. It's weird right now, changes with a stable
  // sprite which is yet to exist
  // Idle: 4 frames, 64x16 cells starting at the sheet's left edge
  m_animations[PlayerState::Idle] =
      Animation(0, 0, 64, 16, 4, 10, true, SheetLayout::Horizontal);

  // Running: 4 frames
  m_animations[PlayerState::Running] =
      Animation(256, 0, 64, 16, 4, 6, true, SheetLayout::Horizontal);

  // Jumping: single frame
  m_animations[PlayerState::Jumping] =
      Animation(512, 0, 64, 16, 1, 10, false, SheetLayout::Horizontal);

  // Falling: 2 frames (see note below)
  m_animations[PlayerState::Falling] =
      Animation(576, 0, 64, 16, 2, 8, false, SheetLayout::Horizontal);
}

void Player::update(double dt, const Input& input,
                    const std::vector<Rect>& solids) {
  float dt_f = static_cast<float>(dt); // Because Rect using floats

  // 1. Horizontal input
  float move_speed = 50.0f;
  m_vx = 0.0f;

  if (input.isHeld(SDL_SCANCODE_A)) {
    m_vx = -move_speed;
    m_facing_right = false;
  }
  if (input.isHeld(SDL_SCANCODE_D)) {
    m_vx = move_speed;
    m_facing_right = true;
  }

  // 2. Handle jump input (Should add buffer time)
  if (input.isPressed(SDL_SCANCODE_W) && m_is_grounded) {
    m_vy = -110.0f;
    m_is_grounded = false;
  }

  // 3. Gravity
  float gravity = 150.0f;
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

  // 6. Determine animation state based on movement & grounded flags
  PlayerState target_state = PlayerState::Idle;
  if (!m_is_grounded) {
    target_state = (m_vy < 0.0f) ? PlayerState::Jumping : PlayerState::Falling;
  } else if (m_vx != 0.0f) {
    target_state = PlayerState::Running;
  } else {
    target_state = PlayerState::Idle;
  }

  // Apply state change
  changeState(target_state);

  // 7. Advance animation tick counter
  m_animations[m_current_state].update();
}

void Player::render(Window& window, Texture& spriteSheet) {
  // Grab source rect from active animation
  SDL_Rect player_src_rect =
      m_animations[m_current_state].getCurrentFrameRect();

  SDL_RendererFlip flip = m_facing_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

  // Our cell isn't aligned with our character, and our character is drawn in
  // the middle of the cell
  int padding_x =
      static_cast<int>(((player_src_rect.w - m_frame_width) / 2.0f) * m_scale);
  int padding_y =
      static_cast<int>(((player_src_rect.h - m_frame_height) / 2.0f) * m_scale);

  spriteSheet.renderEx(window.getRenderer(),
                       static_cast<int>(m_bounds.x) - padding_x,
                       static_cast<int>(m_bounds.y) - padding_y,
                       &player_src_rect, m_scale, flip);

  // Hitbox stuff
  SDL_SetRenderDrawColor(window.getRenderer(), 255, 0, 0, 255);
  SDL_Rect hb{(int)m_bounds.x, (int)m_bounds.y, (int)m_bounds.width,
              (int)m_bounds.height};
  SDL_RenderDrawRect(window.getRenderer(), &hb);
}

void Player::changeState(PlayerState new_state) {
  m_current_state = new_state;

  // Reset the frame counter if transitioning into a new state
  if (m_current_state != m_previous_state) {
    m_animations[m_current_state].reset();
    m_previous_state = m_current_state;
  }
}

PlayerSnapshot Player::save() const {
  PlayerSnapshot snapshot;
  snapshot.bounds = m_bounds;
  snapshot.vx = m_vx;
  snapshot.vy = m_vy;
  snapshot.is_grounded = m_is_grounded;
  snapshot.facing_right = m_facing_right;
  snapshot.current_state = m_current_state;
  snapshot.previous_state = m_previous_state;

  // Save the active animation's exact progress state
  snapshot.animation_state = m_animations.at(m_current_state).getState();

  return snapshot;
}

void Player::restore(const PlayerSnapshot& snapshot) {
  m_bounds = snapshot.bounds;
  m_vx = snapshot.vx;
  m_vy = snapshot.vy;
  m_is_grounded = snapshot.is_grounded;
  m_facing_right = snapshot.facing_right;

  // Restore both states first so changeState's equality check passes cleanly
  m_current_state = snapshot.current_state;
  m_previous_state = snapshot.previous_state;

  // Restore the active animation's frame/tick progress
  m_animations.at(m_current_state).setState(snapshot.animation_state);
}

Rect Player::getBoundingBox() const { return m_bounds; }
