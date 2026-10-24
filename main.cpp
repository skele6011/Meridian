#include <SDL.h>
#include <iostream>

int main() {
  // 1. Initialize SDL2 video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  // 2. Create the window for Meridian
  SDL_Window* window = SDL_CreateWindow("Meridian",             // Window title
                                        SDL_WINDOWPOS_CENTERED, // X position
                                        SDL_WINDOWPOS_CENTERED, // Y position
                                        800, 600,               // Width, Height
                                        SDL_WINDOW_SHOWN        // Flags
  );

  if (!window) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  // 3. Create a hardware-accelerated renderer
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // 4. Main loop flag
  bool running = true;
  SDL_Event event;

  // A simple loop so the window stays open until you close it
  while (running) {
    // Handle window events (like clicking the 'X' button)
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    // Set draw color to a nice dark slate blue, then clear the screen
    SDL_SetRenderDrawColor(renderer, 30, 30, 46, 255);
    SDL_RenderClear(renderer);

    // Show what we just drew on the screen
    SDL_RenderPresent(renderer);
  }

  // 5. Clean up and exit cleanly
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "Meridian shut down successfully." << std::endl;
  return 0;
}
