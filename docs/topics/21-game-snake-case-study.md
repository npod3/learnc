# 21 – Snake Game Case Study

The Snake example ties multiple concepts together: input, timing, dynamic arrays, collision logic, and rendering.

## Components
- Game loop with fixed timestep.
- Input polling (non‑blocking) via `platform.c`.
- Dynamic body storage (array of segments).
- Collision detection (self and walls).
- Rendering with ASCII characters.

## Loop Skeleton
```c
while (!quit) {
    poll_input();
    update_snake();
    if (collision) break;
    draw();
    sleep_ms(50);
}
```

## Learning Goals
- Coordinating multiple modules.
- State management and invariants (head position valid, no overlaps except growth moment).
- Separating update vs render for clarity.

## Extensions
- Add score and food spawning logic variety.
- Persist high scores (serialization example integration).
- Introduce levels or obstacles.

## Pitfalls
- Not clearing screen each frame → visual artifacts.
- Skipping bounds checks leading to memory writes out of range.
