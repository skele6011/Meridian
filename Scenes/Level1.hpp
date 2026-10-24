#pragma once

#include "Level.hpp"

class Level1 : public Level {
public:
  Level1();
  ~Level1() override = default;

  void update(double fixed_dt, const Input& input) override;
  void render(Window& window) override;

private:
  // Simple test player properties
  float m_player_x;
  float m_player_y;
  float m_player_width;
  float m_player_height;
  float m_player_speed;
};
