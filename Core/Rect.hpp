#pragma once

struct Rect {
  float x;
  float y;
  float width;
  float height;

  // Check if this rectangle overlaps with another
  bool intersects(const Rect& other) const {
    return x < other.x + other.width && x + width > other.x &&
           y < other.y + other.height && y + height > other.y;
  }

  // Helpers to get edges easily
  float left() const { return x; }
  float right() const { return x + width; }
  float top() const { return y; }
  float bottom() const { return y + height; }
};
