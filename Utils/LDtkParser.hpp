#pragma once

#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../Core/Rect.hpp"

struct RenderTile {
  int x, y;          // where to draw it in the level (from px)
  SDL_Rect src_rect; // which 8x8 square of tiles.png to copy (from src)
  int flip;          // 0 = none, 1 = flip X, 2 = flip Y, 3 = both (from f)
};

class LDtkParser {
public:
  void loadLevel(const std::string& filepath, const std::string& level_name);

  std::vector<Rect> loadSolids();

  SDL_Point getSpawnPoint();

  std::vector<RenderTile> loadTiles();

private:
  nlohmann::json m_data;
  nlohmann::json m_level;
  int m_level_width;
  int m_level_height;
};
