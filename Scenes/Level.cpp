#include "Level.hpp"
#include "SDL_render.h"
#include <iostream>

// Everything here is everything that should be in EVERY level, if loading
// images for other levels, do that in those specific levels.
void Level::loadBaseAssets(SDL_Renderer* renderer) {
  std::cout << "Loading base assets..." << std::endl;
  m_player_texture.loadFromFile("../assets/Player-Sheet.png", renderer);
};

void Level::update(double fixed_dt, const Input& input) {
  m_player.update(fixed_dt, input, m_solids);
}

//
void Level::render(Window& window) {
  // Things that will always be rendered happen here first

  // Background
  SDL_SetRenderDrawColor(window.getRenderer(), 137, 180, 250, 255);
  SDL_RenderClear(window.getRenderer());

  // Player
  std::cout << "Rendering player at X: " << m_player.getX()
            << " Y: " << m_player.getY() << std::endl;
  m_player.render(window, m_player_texture);
}
