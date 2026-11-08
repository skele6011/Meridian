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
  }
  if (!found) {
    std::cerr << "Level not found in JSON: " << level_name << "\n";
    return;
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

    // If our cell isn't an empty tile, we will add it
    if (cell != 0) {
      solids.push_back(
          {static_cast<float>(x), static_cast<float>(y), 8.0f, 8.0f});
    }
  }
  return solids;
}

SDL_Point LDtkParser::getSpawnPoint() {
  nlohmann::json entities; // Holds json at entities point for easier use
  // Go through layerInstances in Level and find entities layer
  bool found = false;
  for (auto& layer : m_level["layerInstances"]) {
    if (layer["__identifier"] == "Entities") {
      entities = layer;
      found = true;
      break;
    }
  }
  if (!found) {
    std::cerr << "Entities layer not found\n";
    return {};
  }

  // Go through to find Player_Start (used for spawn point) and put them in our
  // variable
  SDL_Point spawnPoint;
  for (auto& entity : entities["entityInstances"]) {
    if (entity["__identifier"] == "Player_Start") {
      spawnPoint.x = entity["px"][0];
      spawnPoint.y = entity["px"][1];
    }
  }

  // Do some maths to go from grid to pixels
  // spawnPoint.x = (spawnPoint.x * 2) * 8;
  // spawnPoint.y = (spawnPoint.y * 2) * 8;

  std::cout << spawnPoint.x << ", " << spawnPoint.y << "<-- Spawn point";
  return spawnPoint;
}
