#include "Window.hpp"
#include "SDL_render.h"
#include <iostream>

Window::Window(const std::string& title, int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    m_is_open = false;
    return;
  }

  m_window =
      SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

  if (!m_window) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    m_is_open = false;
    return;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  if (!m_renderer) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    m_is_open = false;
    return;
  }

  // Force an aspect ratio
  SDL_RenderSetLogicalSize(m_renderer, 1920, 1080);
}

Window::~Window() {
  if (m_renderer)
    SDL_DestroyRenderer(m_renderer);
  if (m_window)
    SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Window::clear() {
  // Catppuccin Mocha background color (30, 30, 46)
  SDL_SetRenderDrawColor(m_renderer, 30, 30, 46, 255);
  SDL_RenderClear(m_renderer);
}

void Window::render() { SDL_RenderPresent(m_renderer); }

bool Window::handleWindowEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false; // Tells the game loop the window is closing
    }
  }
  return true;
}
