#pragma once

#include "../Core/Input.hpp"
#include "../Core/Rect.hpp"
#include "../Core/Window.hpp"
#include "../Entities/Player.hpp"
#include "../Graphics/Texture.hpp"

#include <deque>
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
  SDL_Point m_spawn{100, 100};
  Player m_player{static_cast<float>(m_spawn.x), static_cast<float>(m_spawn.y),
                  8.0f, 16.0f};

  // Time rewind history buffer
  std::deque<PlayerSnapshot> m_player_history;
  const size_t m_max_history_size =
      1200; // ~10 seconds at 120 ticks/sec  TODO: Make it work with any FPS

  // Shared level geometry & triggers (pushed by individual levels)
  std::vector<Rect> m_solids;
  std::vector<Trigger> m_triggers;

  // Shared player texture (1 player, so own by base class (this one))
  Texture m_player_texture;
};
