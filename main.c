#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_log.h>
#include <SDL_mouse.h>
#include <SDL_render.h>
#include <SDL_video.h>

enum {
	WHITE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	CYAN,
	MAGENTA,
	BLACK,
};

SDL_Color colors[8] = {
	{255, 255, 255, SDL_ALPHA_OPAQUE}, // white
	{255, 0, 0, SDL_ALPHA_OPAQUE},	   // red
	{0, 255, 0, SDL_ALPHA_OPAQUE},	   // green
	{0, 0, 255, SDL_ALPHA_OPAQUE},	   // blue
	{255, 255, 0, SDL_ALPHA_OPAQUE},   // yellow
	{0, 255, 255, SDL_ALPHA_OPAQUE},   // cyan
	{255, 0, 255, SDL_ALPHA_OPAQUE},   // magenta
	{0, 0, 0, SDL_ALPHA_OPAQUE},	   // black
};

enum {
	TOP_LEFT,
	TOP_RIGHT,
	MIDDLE_LEFT,
	MIDDLE_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
};

// init in init_global_const()
SDL_FPoint points[6];

// for SDL_RenderGeometry
int indices[6] = {
	TOP_LEFT, TOP_RIGHT,   MIDDLE_RIGHT, // 1st triangle
	TOP_LEFT, MIDDLE_LEFT, MIDDLE_RIGHT, // 2nd triangle
};

int width, height, size;

void init_global_const() {
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0, &mode);
	width = mode.w;
	height = mode.h;
	int a = width, b = height, c; // gcd
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	size = a;
	while (height / size < 10) {
		size /= 2;
	}

	SDL_FPoint _points[6] = {
		{.x = 0, .y = 0},					  // top left
		{.x = width, .y = 0},				  // top right
		{.x = 0, .y = (float)height / 2},	  // middle left
		{.x = width, .y = (float)height / 2}, // middle right
		{.x = 0, .y = height},				  // bottom left
		{.x = width, .y = height},			  // bottom right
	};
	memcpy(points, _points, sizeof(_points));
}

// true to skip draw
bool handle_event(SDL_Event *event, int *stage, bool *quit) {
	switch (event->type) {
	case SDL_QUIT:
		// quit
		*quit = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		// next stage
		(*stage)++;
		break;
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
		case SDLK_c:
			if (SDL_GetModState() & KMOD_CTRL) {
				*quit = true;
			}
			break;
		case SDLK_ESCAPE:
		case SDLK_q:
			// quit
			*quit = true;
			break;
		case SDLK_LEFT:
		case SDLK_UP:
			// previous stage
			(*stage)--;
			break;
		case SDLK_SPACE:
		case SDLK_RIGHT:
		case SDLK_DOWN:
			// next stage
			(*stage)++;
			break;
		}
		break;
	default:
		// first frame need to draw
		if (*stage == 1) {
			return false;
		}
		return true;
	}
	return false;
}

void page_pure_black(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void page_pure_white(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void page_pure_red(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void page_pure_green(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void page_pure_blue(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void page_pure_yellow(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void page_pure_cyan(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void page_pure_magenta(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void page_level(SDL_Renderer *renderer, SDL_Color color) {
	SDL_Vertex vertices[4];

	vertices[0].color = color;
	vertices[1].color = colors[BLACK];
	vertices[2].color = color;
	vertices[3].color = colors[BLACK];

	vertices[0].position = points[TOP_LEFT];
	vertices[1].position = points[TOP_RIGHT];
	vertices[2].position = points[MIDDLE_LEFT];
	vertices[3].position = points[MIDDLE_RIGHT];

	SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);

	vertices[0].position = points[BOTTOM_RIGHT];
	vertices[1].position = points[BOTTOM_LEFT];
	vertices[2].position = points[MIDDLE_RIGHT];
	vertices[3].position = points[MIDDLE_LEFT];

	SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);
}

void page_level_white(SDL_Renderer *renderer) {
	page_level(renderer, colors[WHITE]);
}

void page_level_red(SDL_Renderer *renderer) {
	page_level(renderer, colors[RED]);
}

void page_level_green(SDL_Renderer *renderer) {
	page_level(renderer, colors[GREEN]);
}

void page_level_blue(SDL_Renderer *renderer) {
	page_level(renderer, colors[BLUE]);
}

void page_level_yellow(SDL_Renderer *renderer) {
	page_level(renderer, colors[YELLOW]);
}

void page_level_cyan(SDL_Renderer *renderer) {
	page_level(renderer, colors[CYAN]);
}

void page_level_magenta(SDL_Renderer *renderer) {
	page_level(renderer, colors[MAGENTA]);
}

void page_lines_90(SDL_Renderer *renderer) {
	page_pure_black(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
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
}

void page_lines_45(SDL_Renderer *renderer) {
	page_pure_black(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int b = 0; b <= width + height; b = b + size) {
		SDL_RenderDrawLine(renderer, 0, b - 1, b - 1, 0);
		SDL_RenderDrawLine(renderer, 0, b, b, 0);
		SDL_RenderDrawLine(renderer, width - b + 1, 0, width, b - 1);
		SDL_RenderDrawLine(renderer, width - b, 0, width, b);
	}
}

typedef void (*page_action_ptr)(SDL_Renderer *renderer);

page_action_ptr pages[] = {
	NULL, page_pure_black,
	// pure
	page_pure_white, page_pure_red, page_pure_green, page_pure_blue,
	page_pure_yellow, page_pure_cyan, page_pure_magenta,
	// level
	page_level_white, page_level_red, page_level_green, page_level_blue,
	page_level_yellow, page_level_cyan, page_level_magenta,
	// lines
	page_lines_90, page_lines_45, NULL};

void print_help(char *name) {
	printf("Usage: %s [-m] [-v] [-h]\n", name);
	printf("\tNext     Page: <Space> <Right> <Down> mouse-click\n"
		   "\tPrevious Page: <Left> <Up>\n"
		   "\tQuit     Test: <Ctrl+C> <ESC> <q>\n");
}

void print_modes() {
	SDL_DisplayMode mode;
	int displayNumber = SDL_GetNumVideoDisplays();
	for (int displayIndex = 0; displayIndex < displayNumber; displayIndex++) {
		printf("Display [%d]:\n", displayIndex);
		int modeNumber = SDL_GetNumDisplayModes(displayIndex);
		for (int modeIndex = 0; modeIndex < modeNumber; modeIndex++) {
			SDL_GetDisplayMode(displayIndex, modeIndex, &mode);
			printf("\tMode %2d: %4d-%-4d <%d>\n", modeIndex, mode.w, mode.h,
				   mode.refresh_rate);
		}
	}
}

int main(int argc, char *argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);

	int opt;
	while ((opt = getopt(argc, argv, "mvh")) != -1) {
		switch (opt) {
		case 'm':
			print_modes();
			return 0;
		case 'v':
			// VERSION is defined in Makefile
			printf("%s %s\n", argv[0], VERSION);
			return 0;
		case 'h':
			print_help(argv[0]);
			return 0;
		default:
			print_help(argv[0]);
			return 1;
		}
	}

	init_global_const();
	// set flag to SDL_WINDOW_FULLSCREEN will get wrong size
	SDL_Window *window = SDL_CreateWindow("Display Test", 0, 0, width, height,
										  SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_ShowCursor(SDL_DISABLE);

	int stage = 1;
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		if (!SDL_WaitEvent(&event)) {
			printf("SDL_WaitEvent failed: %s\n", SDL_GetError());
			break;
		}
		if (handle_event(&event, &stage, &quit)) {
			continue;
		}
		// SDL_Log("stage: %d", stage);
		if (pages[stage] == NULL) {
			break;
		}

		pages[stage](renderer);
		SDL_RenderPresent(renderer);
	}
	print_modes();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
