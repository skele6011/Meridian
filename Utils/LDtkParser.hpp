#pragma once

#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../Core/Rect.hpp"

class LDtkParser {
public:
  void loadLevel(const std::string& filepath, const std::string& level_name);

  std::vector<Rect> loadSolids();

  SDL_Point getSpawnPoint();

private:
  nlohmann::json m_data;
  nlohmann::json m_level;
  int m_level_width;
  int m_level_height;
};
