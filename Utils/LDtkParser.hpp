#pragma once 

#include <string>
#include <vector>
#include <SDL.h>
#include "../Core/Rect.hpp"

struct LevelData {
  int width = 0;
  int height = 0;
  std::vector<Rect> solids;
  SDL_Point player_spawn{100, 100}; // Default fallback
};

class LDtkParser {
public:
  // Parses the LDtk JSON export and returns geometry/entity layout for a specific room
  static LevelData loadLevel(const std::string& filepath, const std::string& level_identifier);
};
