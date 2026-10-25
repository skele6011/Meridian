#pragma once

#include "../Core/Input.hpp"
#include "../Core/Rect.hpp"
#include "../Core/Window.hpp"
#include "../Graphics/Texture.hpp"

#include <vector>

// For later
enum class EventType { None = 0, Dialogue, LevelTransition };

// For later
struct Trigger {
  Rect bounds;
  EventType event_type;
};

class Level {
public:
  virtual ~Level() = default;

  virtual void loadBaseAssets(SDL_Renderer* renderer); // For things like images

  // Core loop functions
  virtual void update(double fixed_dt, const Input& input);
  virtual void render(Window& window);

protected:
  // Shared player & physics state
  Rect m_player{100.0f, 100.0f, 24.0f, 36.0f};
  float m_vel_x = 0.0f;
  float m_vel_y = 0.0f;

  // Shared level geometry & triggers (pushed by individual levels)
  std::vector<Rect> m_solids;
  std::vector<Trigger> m_triggers;

  // Shared player texture (1 player, so own by base class (this one))
  Texture m_player_texture;
};
