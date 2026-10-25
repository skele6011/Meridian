#pragma once

#include "Level.hpp"
class Level1 : public Level {
public:
  Level1();
  ~Level1() override = default;

  void render(Window& window) override;

private:
};
