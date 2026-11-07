#pragma once

#include "Level.hpp"
#include "SDL_render.h"
class Level1 : public Level {
public:
  Level1();
  ~Level1() override = default;

  void loadBaseAssets(SDL_Renderer* renderer) override;
  void renderBackground(Window& window) override;
  void render(Window& window) override;

private:
  // Parallax background textures
  Texture m_bg_layer1; // Solid base / farthest
  Texture m_bg_layer2;
  Texture m_bg_layer3;
  Texture m_bg_layer4; // Closest
};
