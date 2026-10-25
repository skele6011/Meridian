#pragma once

#include "../Core/Rect.hpp"
#include "Level.hpp"
#include <vector>
class Level1 : public Level {
public:
  Level1();
  ~Level1() override = default;

  void update(double fixed_dt, const Input& input) override;
  void render(Window& window) override;

private:
  // Simple test player properties
  Rect m_player;
  float m_vel_x;
  float m_vel_y;

  std::vector<Rect> m_solids;
};
