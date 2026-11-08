#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>

#include "../Core/Input.hpp"
#include "../Core/Rect.hpp"
#include "../Core/Window.hpp"
#include "../Graphics/Animation.hpp"
#include "../Graphics/Texture.hpp"

enum class PlayerState { Idle, Running, Jumping, Falling };

struct PlayerSnapshot {
  Rect bounds;
  float vx;
  float vy;
  bool is_grounded;
  bool facing_right;
  PlayerState current_state;
  PlayerState previous_state;
  Animation::State animation_state;
};

class Player {
public:
  Player(float start_x, float start_y, float width, float height);
  ~Player() = default;

  // Core update and render loop functions
  void update(double dt, const Input& input, const std::vector<Rect>& solids);
  void render(Window& window, Texture& spriteSheet, float camera_x,
              float camera_y);

  // Getters for position and boundaries
  Rect getBoundingBox() const;
  float getX() const { return m_bounds.x; }
  float getY() const { return m_bounds.y; }

  // For time rewinding
  PlayerSnapshot save() const;
  void restore(const PlayerSnapshot& snapshot);

private:
  // Position and velocity
  Rect m_bounds;
  float m_vx;
  float m_vy;

  // Sprite configuration dimensions
  int m_frame_width;
  int m_frame_height;
  float m_scale;

  // Physics state flags
  bool m_is_grounded;
  // Might add things for wall sliding here later

  // State & Animation management
  PlayerState m_current_state;
  PlayerState m_previous_state;
  bool m_facing_right;
  // Animation collectionf or each state
  std::unordered_map<PlayerState, Animation> m_animations;

  // Helper method to switch states and reset animation frames
  void changeState(PlayerState new_state);
};
