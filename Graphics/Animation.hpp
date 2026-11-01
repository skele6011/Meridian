#pragma once

#include <SDL.h>

// Determines how frames are laid out on the sprite sheet texture
enum class SheetLayout {
  Horizontal, // Frames arranged left to right in a row
  Vertical    // Frames arranged top to bottom in a column
};

class Animation {
public:
  Animation() = default;

  // Configurable constructor for flexible spritesheet layouts
  Animation(int start_x, int start_y, int frame_w, int frame_h,
            int total_frames, int ticks_per_frame, bool loop = true,
            SheetLayout layout = SheetLayout::Horizontal);

  // Advance animation frame counter based on fixed tick updates
  void update();

  // Reset animation back to the initial frame (crucial for state transitions)
  void reset();

  // Calculate and return the active source SDL_Rect on the spritesheet
  SDL_Rect getCurrentFrameRect() const;

  // Query if a non-looping animation has reached its final frame
  bool isFinished() const;

private:
  int m_start_x;
  int m_start_y;
  int m_frame_width;
  int m_frame_height;
  int m_total_frames;
  int m_ticks_per_frame;
  bool m_loop;
  SheetLayout m_layout;

  int m_current_frame;
  int m_tick_counter;
  bool m_is_finished;
};
