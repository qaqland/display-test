# Display Test

> [!WARNING]  
> **PHOTOSENSITIVITY/EPILEPSY SEIZURES**

Test your display with colors and lines.

- color pure \* 8
- color level \* 7
- lines \* 2

## Build

Only need `libsdl2-dev`, `libsdl2-devel` or `sdl2-dev`

Run `make` to build it.

## Usage

see `display-test -h`

## Wayland

```
SDL_VIDEODRIVER=wayland ./display-test
```

## Scripts for Development

```
apk add sdl2-dev bear
bear -- make
```

