#pragma once

#include <SDL.h>
#include <string>

class Window {
public:
  Window(const std::string& title, int width, int height);
  ~Window();

  // Prevent copying to avoid double-freeing SDL windows
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  bool isOpen() const { return m_is_open; }
  void clear();
  void render();
  bool handleWindowEvents(); // Return false if "X" is clicked

  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

private:
  SDL_Window* m_window = nullptr;
  SDL_Renderer* m_renderer = nullptr;
  bool m_is_open = true;
  int m_width;
  int m_height;
};
