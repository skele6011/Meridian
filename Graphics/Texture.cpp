#include "Texture.hpp"
#include "SDL_render.h"
#include "SDL_surface.h"
#include <SDL_image.h>
#include <iostream>

Texture::Texture() : m_texture(nullptr), m_width(0), m_height(0) {}

Texture::~Texture() { free(); }

Texture::Texture(Texture&& other) noexcept
    : m_texture(other.m_texture), m_width(other.m_width),
      m_height(other.m_height) {
  // Clear out second texture (we moved 2 to 1 in member initialization list)
  other.m_texture = nullptr;
  other.m_width = 0;
  other.m_height = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
  if (this != &other) { // Prevents dummy moves like tex = std::move(tex);
    free();
    // Move second texture to first texture
    m_texture = other.m_texture;
    m_width = other.m_width;
    m_height = other.m_height;
    // Clear out second texture
    other.m_texture = nullptr;
    other.m_width = 0;
    other.m_height = 0;
  }
  return *this; // Return reference to currnet object incase we want to chain
}

bool Texture::loadFromFile(const std::string& path, SDL_Renderer* renderer) {
  free(); // Clean up any prior texture

  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == nullptr) {
    std::cerr << "Failed to load image" << path
              << "! SDL_image Error: " << IMG_GetError() << "\n";
    return false;
  }

  m_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
  if (m_texture == nullptr) {
    std::cerr << "Failed to create texture from " << path
              << "! SDL Error: " << SDL_GetError() << "\n";
  } else {
    m_width = loaded_surface->w;
    m_height = loaded_surface->h;
  }

  SDL_FreeSurface(loaded_surface); // Useless; we got our texture already
  return m_texture != nullptr;     // Only if it exists
}

void Texture::free() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
  }
}

void Texture::render(SDL_Renderer* renderer, int x, int y,
                     const SDL_Rect* src_rect, float scale) const {

  SDL_Rect dst_rect = {x, y, m_width, m_height};

  if (src_rect != nullptr) {
    dst_rect.w = src_rect->w;
    dst_rect.h = src_rect->h;
  }

  // Apply global or per-sprite scale factor cleanly in one place
  dst_rect.w = static_cast<int>(dst_rect.w * scale);
  dst_rect.h = static_cast<int>(dst_rect.h * scale);

  SDL_RenderCopy(renderer, m_texture, src_rect, &dst_rect);
}
