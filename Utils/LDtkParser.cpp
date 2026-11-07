#include "LDtkParser.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

LevelData LDtkParser::loadLevel(const std::string& filepath, const std::string &level_identifier) {
  LevelData data;

  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Error: Failed to open LDtk file at " << filepath << "\n";
    return data;
  }

  nlohmann::json j;
  file >> j;

  // Find the requested level by its identifier string 
  for (const auto& level : j["levels"]) {
    if (level["identifier"] == level_identifier) {
      data.width = level["pxWid"];
      data.height = level["pxHei"];

      // Iterate through layer instances 
      for (const auto& layer : level["layerInstances"]) {
        std::string type = layer["__type"];
        int grid_size = layer["__gridSize"];

        // Parise IntGrid collision layer 
        if (type == "IntGrid") {
          auto csv = layer["intGridCsv"];
          int c_width = layer["__cWid"];

          for (size_t i = 0; i < csv.size(); ++i) {
            int val = csv[i];
            if (val != 0) { // Non-zero indicates a solid block
              int gx = (i % c_width) * grid_size;
              int gy = (i / c_width) * grid_size;
              data.solids.push_back({
                  static_cast<float>(gx),
                  static_cast<float>(gy),
                  static_cast<float>(grid_size),
                  static_cast<float>(grid_size)
                  });
            }
          }
        }
        // Parse Entity Layer for spawn points 
        else if (type == "Entities") {
          for (const auto& entity : layer["entityInstances"]) {
            if (entity["__identifier"] == "Player_Start") {
              auto px = entity["px"];
              data.player_spawn = {px[0], px[1]};
            }
          }
        }
      }
      break;
    }
  }
  return data;
}
