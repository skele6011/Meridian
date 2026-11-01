#include "Animation.hpp"

Animation::Animation(int start_x, int start_y, int frame_w, int frame_h,
                     int total_frames, int ticks_per_frame, bool loop,
                     SheetLayout layout)
    : m_start_x(start_x), m_start_y(start_y), m_frame_width(frame_w),
      m_frame_height(frame_h), m_total_frames(total_frames),
      m_ticks_per_frame(ticks_per_frame), m_loop(loop), m_layout(layout),
      m_current_frame(0), m_tick_counter(0), m_is_finished(false) {}

void Animation::update() {
  // Do not advance further if a non-looping animation has completed
  if (m_is_finished && !m_loop) {
    return;
  }

  // Accumulate ticks and step to the next frame when threshold is met
  m_tick_counter++;
  if (m_tick_counter >= m_ticks_per_frame) {
    m_tick_counter = 0;
    m_current_frame++;

    // Handle loop wrapping or completion limits
    if (m_current_frame >= m_total_frames) {
      if (m_loop) {
        m_current_frame = 0;
      } else {
        m_current_frame = m_total_frames - 1;
        m_is_finished = true;
      }
    }
  }
}

void Animation::reset() {
  m_current_frame = 0;
  m_tick_counter = 0;
  m_is_finished = false;
}

SDL_Rect Animation::getCurrentFrameRect() const {
  SDL_Rect rect{m_start_x, m_start_y, m_frame_width, m_frame_height};

  // Calculate source coordinates depending on whether the strip is horizontal
  // or vertical
  if (m_layout == SheetLayout::Horizontal) {
    rect.x += m_current_frame * m_frame_width;
  } else {
    rect.y += m_current_frame * m_frame_height;
  }

  return rect;
}

bool Animation::isFinished() const { return m_is_finished; }

Animation::State Animation::getState() const {
  return {m_current_frame, m_tick_counter, m_is_finished};
}

void Animation::setState(const State& state) {
  m_current_frame = state.current_frame;
  m_tick_counter = state.tick_counter;
  m_is_finished = state.is_finished;
}
