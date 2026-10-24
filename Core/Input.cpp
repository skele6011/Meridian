#include "Input.hpp"

Input::Input() {
  std::memset(m_current_keys, 0, sizeof(m_current_keys));
  std::memset(m_previous_keys, 0, sizeof(m_previous_keys));
}

void Input::update() {
  // 1. Copy current state to previous state before updating
  std::memcpy(m_previous_keys, m_current_keys, sizeof(m_current_keys));

  // 2. Fetch the fresh keyboard state directly from SDL
  int numkeys;
  const Uint8* sdl_state = SDL_GetKeyboardState(&numkeys);

  // Copy as many keys as SDL provides safely
  int bytes_to_copy =
      (numkeys < SDL_NUM_SCANCODES) ? numkeys : SDL_NUM_SCANCODES;
  std::memcpy(m_current_keys, sdl_state, bytes_to_copy);
}

bool Input::isHeld(SDL_Scancode key) const { return m_current_keys[key] != 0; }

bool Input::isPressed(SDL_Scancode key) const {
  return m_current_keys[key] != 0 && m_previous_keys[key] == 0;
}

bool Input::isReleased(SDL_Scancode key) const {
  return m_current_keys[key] == 0 && m_previous_keys[key] != 0;
}
