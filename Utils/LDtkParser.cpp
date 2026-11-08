#include "LDtkParser.hpp"
#include "nlohmann/json_fwd.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

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

nlohmann::json LDtkParser::findLayer(const std::string& name) {
  nlohmann::json returned_layer;
  bool found = false;
  for (auto& layer : m_level["layerInstances"]) {
    if (layer["__identifier"] == name) {
      returned_layer = layer;
      found = true;
      break;
    }
  }

  if (!found) {
    std::cerr << name << " layer not found\n";
    return {};
  }

  return returned_layer;
}

std::vector<Rect> LDtkParser::loadSolids() {
  nlohmann::json csv; // Holds the integer grid csv
  nlohmann::json layer = this->findLayer("Collision");
  if (layer.is_null())
    return {};
  csv = layer["intGridCsv"];

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
  // Holds json at layer entities point for easier use
  nlohmann::json entities = this->findLayer("Entities");
  if (entities.is_null())
    return {};

  // Go through to find Player_Start (used for spawn point) and put them in our
  // variable
  SDL_Point spawnPoint{100, 100};
  for (auto& entity : entities["entityInstances"]) {
    if (entity["__identifier"] == "Player_Start") {
      spawnPoint.x = entity["px"][0];
      spawnPoint.y = entity["px"][1];
    }
  }

  return spawnPoint;
}

std::vector<RenderTile> LDtkParser::loadTiles(const std::string& layer_name) {
  nlohmann::json tile_list; // Holds the autoLayerTiles list

  nlohmann::json layer = this->findLayer(layer_name);
  if (layer.is_null())
    return {};
  tile_list = layer["autoLayerTiles"];

  std::vector<RenderTile> tiles; // What will be returned
  for (auto& tile : tile_list) {
    int px_x = tile["px"][0]; // Where in the level
    int px_y = tile["px"][1];
    int src_x = tile["src"][0];
    int src_y = tile["src"][1];
    int flip = tile["f"];

    RenderTile t;
    t.x = px_x;
    t.y = px_y;
    t.src_rect = {src_x, src_y, 8, 8}; // x, y, width, height
    t.flip = flip;
    tiles.push_back(t);
  }
  return tiles;
}
