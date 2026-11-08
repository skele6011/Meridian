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
- [x] **Step 1: Map Editor Format Selection**
  - Choose and configure an external map format (such as Tiled JSON or CSV exports) for level creation.
  - Establish final tile and sprite dimensions.

- [x] **Step 2: Level Map Parser Implementation**
  - Implement a map parsing utility to read layout data and dynamically generate collision solids (`m_solids`).

- [x] **Step 3: Dedicated Player Class Refactor**
  - Extract player state, dimensions, and movement variables into a dedicated `Player` class now that final art assets and sizes are established.

- [ ] **Step 4: Player Spawn from Map Data** 
  - Read the `Player_Start` entity from the Entities layer and store its position in the parser.
  - Replace the hardcoded (100, 100) player position in `Level1` with the parsed spawn point.

- [ ] **Step 5: Tile Texture Rendering (Collision Layer Art)**
  - Read the `autoLayerTiles` list from the Collision layer (pixel position, tileset source position, flip value).
  - Store the tiles in a visual-only list, separate from `m_solids`.
  - Draw them with the tileset texture, applying horizontal/vertical flips.
  - Remove the red debug outlines once the art matches the collision.

- [ ] **Step 6: Camera**
  - Offset all drawing by a camera position that follows the player.
  - Clamp the camera to the level's pixel width and height so it never shows outside the map.

- [ ] **Step 7: Backgrounds**
  - Read the background `AutoLayer` tiles and draw them behind the Collision tiles.
  - Decide how it combines with the parallax PNG layers (the AutoLayer's fill tile may cover them).
  - Draw the parallax layers back to front, with each layer scrolling slower than the camera.

- [ ] **Step 8: Parser Cleanup**
  - Read the grid size and column count from the JSON (`__gridSize`, `__cWid`) instead of hardcoding 8 and 80.
  - Pull the repeated "find a layer by name" loop into one helper function.
  - Remove the duplicate tileset texture in `Level1`.

## 5: Sprite Animations & States
- [x] **Step 1: Animation Component / Struct Design**
  - Define frame duration, total frames, current frame tracker, and looping/non-looping flags.

- [x] **Step 2: Sheet Index Math & Cropping**
  - Automate horizontal/vertical source rect calculations based on the 8x16 grid offset (`X = 28 + (frame_index * 8)`).
  - This will be changed later in terms of exact numbers once we decide on an exact sprite to use.

- [x] **Step 3: State Machine Integration**
  - Link player movement states (Idle, Running, Jumping, Falling) to trigger the correct animation

## 6: Time Rewind Prototype (Snapshots)
- [x] **Step 1: Split Animation into config vs. progress**
  - Add an `Animation::State { frame, tick, finished }` struct.
  - Add `getState()` and `setState()` so the animation’s progress can be saved and loaded without copying the whole object.
  - Give the member ints default values while you’re in there.
- [x] **Step 2: PlayerSnapshot + save/restore**
  - Define `PlayerSnapshot` holding bounds, `vx, vy`, grounded, facing, current and previous state, and the active animation’s State.
  - Implement `Player::save()` and `Player::restore()`.
  - Restore both state and prev_state, otherwise `changeState` resets the animation on the next tick.
- [x] **Step 3: History buffer in Level**
  - Add a `std::deque<PlayerSnapshot>` (or a fixed ring buffer) to Level.
  - Push one snapshot per fixed tick, before `m_player.update`.
  - Cap the length (`e.g. 120 x 10 ticks = 10 seconds`) and drop the oldest.
- [x] **Step 4: Rewind input**
  - While R is held and the buffer isn’t empty: pop the newest snapshot, restore it, and skip the normal update.
  - When the buffer runs out, rewinding just stops. Decide whether the player keeps control or stays frozen.
  - On release, normal simulation resumes from the restored state.
- [x] **Step 5: Test the feel**
  - Try different rewind speeds (1 snapshot per tick is real-time, 2 is double speed).
  - Add a temporary visual cue (tint, or draw the buffer length) so you can tell it’s working.
  - Decide whether this is the mechanic you want before building more on it.
- [ ] **Step 6 (later): Generalize**
  - Once moving platforms or enemies exist, give them the same `save()/restore()` pair, and have Level snapshot everything together as one world snapshot.
  - Rewinding the world is then the same loop, applied to more things.
