#pragma once

#include "../Scenes/Level.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include <memory>

#include "../Scenes/Level1.hpp" // IWYU pragma: keep

class Game {
public:
  Game();
  ~Game() = default;

  void run();

private:
  Window m_window;
  Input m_input;
  std::unique_ptr<Level> m_current_level;
  bool m_is_running;
};
