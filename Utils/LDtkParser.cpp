#include "LDtkParser.hpp"
#include "nlohmann/json_fwd.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

void LDtkParser::loadLevel(const std::string& filepath,
                           const std::string& level_name) {
  // 1. open the file and parse it into a json object
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open LDtk file: " << filepath << "\n";
    return;
  }

  try {
    file >> m_data;
  } catch (const nlohmann::json::parse_error& e) {
    std::cerr << "Error parsing LDtk JSON: " << e.what() << "\n";
    return;
  }
  file.close();

  // Find level we are looking for
  bool found = false;
  for (auto& lvl : m_data["levels"]) {
    if (lvl["identifier"] == level_name) {
      m_level = lvl;
      found = true;
      std::cout << "Level found" << "\n";
      break;
    }
    if (!found) {
      std::cerr << "Level not found in JSON: " << level_name << "\n";
      return;
    }
  }

  // Get basic information from that level
  m_level_width = m_level["pxWid"];
  m_level_height = m_level["pxHei"];
}

std::vector<Rect> LDtkParser::loadSolids() {
  nlohmann::json csv; // Holds the integer grid csv
  // Go through layerInstances in Level and find collision
  bool found = false;
  for (auto& layer : m_level["layerInstances"]) {
    if (layer["__identifier"] == "Collision") {
      csv = layer["intGridCsv"];
      found = true;
      break;
    }
  }
  if (!found) {
    std::cerr << "Collision layer not found\n";
    return {};
  }

  std::vector<Rect> solids; // What will be returned
  // Loop through the grid and adds the tiles
  for (size_t i = 0; i < csv.size(); ++i) {
    int cell = csv[i]; // The value/type of tile

    // Math
    int x = i % 80;
    x = x * 8;
    int y = i / 80;
    y = y * 8;

    // If our cell isn't an empty tile
    if (cell != 0) {
      solids.push_back(
          {static_cast<float>(x), static_cast<float>(y), 8.0f, 8.0f});
    }
  }
  return solids;
}
