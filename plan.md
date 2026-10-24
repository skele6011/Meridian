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

- [ ] **Step 3: Basic AABB Collision & Physics**
  - Implement simple box collisions so our player can stand on a platform instead of falling forever into the void.

- [ ] **Step 4: Integrating Fixed Timestep with Physics**
  - Wire our `120Hz` fixed delta time (`FIXED_DT`) directly into the player's movement math so it's completely deterministic.

