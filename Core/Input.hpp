#pragma once

#include <SDL.h>
#include <cstring> // IWYU pragma: keep

class Input {
public:
  Input();

  // Call once per frame before processing game logic
  void update();

  // Query functions
  bool isHeld(SDL_Scancode key) const;     // Held down continuously
  bool isPressed(SDL_Scancode key) const;  // Pressed down *this exact frame*
  bool isReleased(SDL_Scancode key) const; // Released *this exact frame*

private:
  // SDL provides up to SDL_NUM_SCANCODES keys
  Uint8 m_current_keys[SDL_NUM_SCANCODES];
  Uint8 m_previous_keys[SDL_NUM_SCANCODES];
};
