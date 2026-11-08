#include "Level1.hpp"

#include <iostream>

Level1::Level1() {

  // Test
  m_parser.loadLevel("../assets/practice_1.ldtk", "Level_0");

  // Spawn point of player
  m_spawn = m_parser.getSpawnPoint();
  m_player = {static_cast<float>(m_spawn.x), static_cast<float>(m_spawn.y),
              8.0f, 16.0f};

  // Fill sizes
  m_level_width = m_parser.getLevelWidth();
  m_level_height = m_parser.getLevelHeight();

  // Collision solids
  std::vector<Rect> solids = m_parser.loadSolids();

  // Visual tiles for collision
  std::vector<RenderTile> tiles = m_parser.loadTiles("Collision");
  std::cout << "Tiles: " << tiles.size() << "\n";
}

void Level1::render(Window& window) {
  // CORE!!! Let base class draw all main things (clear screen, player, etc)
  Level::render(window);

  // Draw level 1 specific things (currently solids)
  // SDL_SetRenderDrawColor(window.getRenderer(), 100, 100, 110, 255);
  // for (const auto& solid : m_solids) {
  //   SDL_Rect solid_rect = {static_cast<int>(solid.x),
  //   static_cast<int>(solid.y),
  //                          static_cast<int>(solid.width),
  //                          static_cast<int>(solid.height)};
  //   SDL_RenderFillRect(window.getRenderer(), &solid_rect);
  // }
}
