#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_mouse.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int gcd(int a, int b) {
  while (b != 0) {
    int temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

int main(int argc, char *argv[]) {

  if (argc > 1) {
    printf("display-test %s\n", VERSION); // VERSION is defined in Makefile
    printf("Test your display with colors and lines.\n");
    printf("Usage: %s\n", argv[0]);
    return 1;
  }

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window = SDL_CreateWindow(
      "Display Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100,
      200, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  int width, height;

  SDL_GetWindowSize(window, &width, &height);
  SDL_Log("Window created: %dx%d", width, height);

  SDL_ShowCursor(SDL_DISABLE);

  bool quit = false;
  int stage = 0;
  int size = gcd(width, height);
  SDL_Event event;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        // debug
        case SDLK_d:
          stage = 8;
          break;
        // next stage
        case SDLK_SPACE:
        case SDLK_RIGHT:
        case SDLK_DOWN:
          stage++;
          break;
        // previous stage
        case SDLK_LEFT:
        case SDLK_UP:
          stage--;
          break;
        // quit
        case SDLK_ESCAPE:
        case SDLK_q:
          quit = true;
          break;
        }
      }
    }

    switch (stage) {
    case 0:
      // white
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderClear(renderer);
      break;
    case 1:
      // red
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderClear(renderer);
      break;
    case 2:
      // green
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      SDL_RenderClear(renderer);
      break;
    case 3:
      // blue
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      SDL_RenderClear(renderer);
      break;
    case 4:
      // yellow
      SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
      SDL_RenderClear(renderer);
      break;
    case 5:
      // cyan
      SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
      SDL_RenderClear(renderer);
      break;
    case 6:
      // magenta
      SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
      SDL_RenderClear(renderer);
      break;
    case 7:
      // black
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      break;
    case 8:
      // gray level
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      for (int g = 0; g < 256; g++) {
        SDL_SetRenderDrawColor(renderer, g, g, g, 255);
        int column = g / 16;
        int row = g % 16;
        float rectWidth = (float)width / 16;
        float rectHeight = (float)height / 16;
        SDL_FRect rect = {.x = row * rectWidth,
                          .y = column * rectHeight,
                          .w = rectWidth,
                          .h = rectHeight};
        SDL_RenderFillRectF(renderer, &rect);
      }
      break;
    case 9:
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      // horizontal lines
      for (int i = 0; i <= height; i = i + size) {
        SDL_RenderDrawLine(renderer, 0, i - 1, width, i - 1);
        SDL_RenderDrawLine(renderer, 0, i, width, i);
      }
      // vertical lines
      for (int i = 0; i <= width; i = i + size) {
        SDL_RenderDrawLine(renderer, i - 1, 0, i - 1, height);
        SDL_RenderDrawLine(renderer, i, 0, i, height);
      }
      break;
    case 10:
      // 45 degree lines
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      for (int b = 0; b <= width + height; b = b + size) {
        SDL_RenderDrawLine(renderer, 0, b - 1, b - 1, 0);
        SDL_RenderDrawLine(renderer, 0, b, b, 0);
        SDL_RenderDrawLine(renderer, width - b + 1, 0, width, b - 1);
        SDL_RenderDrawLine(renderer, width - b, 0, width, b);
      }
      break;
    default:
      // quit
      quit = true;
      continue;
    }
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}