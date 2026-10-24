#pragma once

#include "Input.hpp"
#include "Window.hpp"

class Game {
public:
  Game();
  ~Game() = default;

  void run();

private:
  Window m_window;
  Input m_input;
  bool m_is_running;
};
