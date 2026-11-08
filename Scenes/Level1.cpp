#include "Level1.hpp"

#include <iostream>

Level1::Level1() {
  // Test
  m_level.loadLevel("../assets/practice_1.ldtk", "Level_0");

  std::vector<Rect> solids = m_level.loadSolids();
  std::cout << "Solids: " << solids.size() << "\n";
  std::cout << solids[0].x << ", " << solids[0].y << "\n";

  for (auto& cell : solids) {
    m_solids.push_back(cell);
  }
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
