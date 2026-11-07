#include "Level1.hpp"
#include "SDL_render.h"
#include "../Utils/LDtkParser.hpp"

Level1::Level1() {
  // 1. Load level data dynamically from LDtk JSON file
  // Pass the file path and the specific level identifier set in LDtk
  LevelData data = LDtkParser::loadLevel("../assets/practice_1.ldtk", "Level_0");

  // 2. Assign parsed collision solids to the base class vector 
  m_solids = data.solids;

  // 3. Position the player at the LDtk entity spawn point coordinates
  m_player = Player(static_cast<float>(data.player_spawn.x), static_cast<float>(data.player_spawn.y), 8.0f, 16.0f);
}

void Level1::loadBaseAssets(SDL_Renderer* renderer) {
  // Call base assets first
  Level::loadBaseAssets(renderer);

  // Load level 1 background layers
  m_bg_layer1.loadFromFile("../assets/purple_L1.png", renderer);
  m_bg_layer2.loadFromFile("../assets/purple_L2.png", renderer);
  m_bg_layer3.loadFromFile("../assets/purple_L3.png", renderer);
  m_bg_layer4.loadFromFile("../assets/purple_L4.png", renderer);
}

void Level1::renderBackground(Window& window) {
  SDL_Renderer* renderer = window.getRenderer();

  // Calculate a basic parallax offset based on player X position
  // (Farthest layers move slower, closest layers move faster)
  float player_x = m_player.getX();

  int offset_l1 = static_cast<int>(player_x * 0.05f);
  int offset_l2 = static_cast<int>(player_x * 0.15f);
  int offset_l3 = static_cast<int>(player_x * 0.3f);
  int offset_l4 = static_cast<int>(player_x * 0.45f);

  // Render background layers from back to front
  // Using modulo to loop seamlessly
  m_bg_layer1.render(renderer, -offset_l1 % 320, 0);
  m_bg_layer2.render(renderer, -offset_l2 % 320, 0);
  m_bg_layer3.render(renderer, -offset_l3 % 320, 0);
  m_bg_layer4.render(renderer, -offset_l4 % 320, 0);
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
