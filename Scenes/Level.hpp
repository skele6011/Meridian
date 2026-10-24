#pragma once

#include "../Core/Input.hpp"
#include "../Core/Window.hpp"

class Level {
public:
  virtual ~Level() = default;

  // Virtual functions that every map must override (= 0 means it doesn't exist
  // without being rewritten)
  virtual void update(double fixed_dt, const Input& input) = 0;
  virtual void render(Window& window) = 0;
};
