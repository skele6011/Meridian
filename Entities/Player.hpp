#pragma once
#include <SDL.h>
#include <vector>

#include "../Core/Input.hpp"
#include "../Core/Rect.hpp"
#include "../Core/Window.hpp"
#include "../Graphics/Texture.hpp"

class Player {
public:
  Player(float start_x, float start_y, float width, float height);
  ~Player() = default;

  // Core update and render loop functions
  void update(double dt, const Input& input, const std::vector<Rect>& solids);
  void render(Window& window, Texture& spriteSheet);

  // Getters for position and boundaries
  Rect getBoundingBox() const;
  float getX() const { return m_bounds.x; }
  float getY() const { return m_bounds.y; }

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

  // Internal collision helper
  void handleCollisions(const std::vector<Rect>& solids);
};
