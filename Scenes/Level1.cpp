#include "Level1.hpp"

Level1::Level1() {
  // Add Level 1 specific solids
  m_solids.push_back({0.0f, 900.0f, 1920.0f, 180.0f});
  m_solids.push_back({400.0f, 700.0f, 200.0f, 200.0f});
}

void Level1::render(Window& window) {
  // CORE!!! Let base class draw all main things (clear screen, player, etc)
  Level::render(window);

  // Draw level 1 specific things (currently solids)
  SDL_SetRenderDrawColor(window.getRenderer(), 100, 100, 110, 255);
  for (const auto& solid : m_solids) {
    SDL_Rect solid_rect = {static_cast<int>(solid.x), static_cast<int>(solid.y),
                           static_cast<int>(solid.width),
                           static_cast<int>(solid.height)};
    SDL_RenderFillRect(window.getRenderer(), &solid_rect);
  }
}
