#pragma once

#include "../Core/Input.hpp"
#include "../Core/Rect.hpp"
#include "../Core/Window.hpp"
#include "../Graphics/Texture.hpp"

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

  // Virtual functions that every map must override (= 0 means it doesn't exist
  // without being rewritten)
  virtual void update(double fixed_dt, const Input& input) = 0;
  virtual void render(Window& window) = 0;
};
