## 1: Basics
- [x] Cross-platform CMake build setup
- [x] Window management module (Window.cpp/hpp)
- [x] Input manager (raw state tracking)
- [x] Fixed-timestep game loop & delta time management

## 2: Levels & Entities
- [x] **Step 1: The `Level` Base Class / Interface**
  - Define a clean interface (`virtual void update(double dt, const Input& input) = 0;` and `virtual void render(Window& window) = 0;`).
  - Let `Game` hold a pointer to the active `Level`.

- [x] **Step 2: A Test Level (`Level1`)**
  - Create a concrete level implementation.
  - Spin up a basic player entity (even if it's just a colored rectangle for now) to test movement and input.

- [x] **Step 3: Basic AABB Collision & Physics**
  - Implement simple box collisions so our player can stand on a platform instead of falling forever into the void.

- [x] **Step 4: Integrating Fixed Timestep with Physics**
  - Wire our `120Hz` fixed delta time (`FIXED_DT`) directly into the player's movement math so it's completely deterministic.

## 3: Art & Texture Pipeline
- [x] **Step 1: Integrate `SDL_image`**
  - Add and link the `SDL_image` library into the CMake build setup.
  - Ensure external image loading dependencies compile cleanly across targets.

- [x] **Step 2: Texture Loading and Management**
  - Implement texture loading functions using `IMG_Load` and `SDL_CreateTextureFromSurface`.
  - Build a lightweight wrapper around `SDL_Texture*` to manage resource lifetimes cleanly.

- [x] **Step 3: Sprite Rendering Upgrade**
  - Upgrade the rendering pipeline from primitive shapes (`SDL_RenderFillRect`) to full textures (`SDL_RenderCopy`).
  - Verify asset loading and rendering end-to-end with a temporary test sprite.

## 4: Map Loading & Architecture Refactoring (Post-Art)
- [ ] **Step 1: Map Editor Format Selection**
  - Choose and configure an external map format (such as Tiled JSON or CSV exports) for level creation.
  - Establish final tile and sprite dimensions.

- [ ] **Step 2: Level Map Parser Implementation**
  - Implement a map parsing utility to read layout data and dynamically generate collision solids (`m_solids`).

- [ ] **Step 3: Dedicated Player Class Refactor**
  - Extract player state, dimensions, and movement variables into a dedicated `Player` class now that final art assets and sizes are established.
