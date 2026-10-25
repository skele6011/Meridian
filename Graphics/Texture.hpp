#include <SDL.h>
#include <string>

class Texture {
public:
  Texture();
  ~Texture();

  // Prevent copying to avoid double-freeing SDL_Texture pointers
  // "= delete`` = banning copying. This bans initialization copying.
  Texture(const Texture&) = delete;
  // Bans reassignment copying as well
  Texture& operator=(const Texture&) = delete;

  // Enable move semantics
  Texture(Texture&& other) noexcept;
  Texture& operator=(Texture&& other) noexcept;

  // Core pipeline functions
  bool loadFromFile(const std::string& path, SDL_Renderer* renderer);
  void free();

  // Centralized render function (handles frame clipping)
  void render(SDL_Renderer* rednerer, int x, int y,
              const SDL_Rect* src_rect = nullptr, float scale = 1.0f) const;

  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

private:
  SDL_Texture* m_texture;
  int m_width;
  int m_height;
};
