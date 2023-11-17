# Display Test

Test your display with colors and lines.

## TODO

- Linux
  - Wayland
  - X11
  - FB
- mouse support
  - ~~click~~
  - wheel
- ~~CPU cost~~
- more tests
  - http://www.lagom.nl/lcd-test/sharpness.php
  - https://www.color.org/browsertest.xalter

## Wayland

```
SDL_VIDEODRIVER=wayland ./display-test
```

## Keys

- up/down/left/right/space/escape/q(uit)
- "d" for debug only, no other meaning.

## Scripts for Development

```
apk add sdl2-dev bear
bear -- make
```
