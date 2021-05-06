#include "lib/canvas.h"
#include "lib/error.h"
#include "lib/fonts.h"
#include "lib/grid.h"
#include "lib/icon.h"
#include "lib/button.h"
#include <SDL.h>
#include <stdio.h>

#pragma mark DEFINITIONS

#define APP_NAME "Indic"
#define WINDOW_WIDTH 525
#define WINDOW_HEIGHT 403

#define FPS 30

#define ICON_GRID_POS_X 0
#define ICON_GRID_POS_Y 0
#define ICON_GRID_SIZE_X 8
#define ICON_GRID_SIZE_Y 8
#define ICON_GRID_CELL_SIZE 40
#define ICON_GRID_CELL_PAD 4
#define ICON_GRID_CELL_BORDER 2

#define FONT_SCALE 4

#pragma mark GLOBAL VARIABLES

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

canvas *cCanvas;
grid *iconGrid;
icon *cIcon;
Uint8 *iconData;
button *clearButton;
button *exitButton;

#pragma mark CALLBACKS

void
icon_grid_on_click(grid *g, Uint32 x, Uint32 y)
{
	grid_switch(g, x, y);
}

void
clear_button_on_click(button *b, Uint32 x, Uint32 y)
{
	grid_reset(iconGrid, OFF);
}

void destroy(void); // Forward declaration

void
exit_button_on_click(button *b, Uint32 x, Uint32 y)
{
	destroy();
	exit(0);
}

#pragma mark INITIALIZATION & DESTRUCTION

void
init_app()
{
	// SDL & Memory allocation
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		error("SDL_Init Failed", SDL_GetError());
		exit(1);
	}
	window = SDL_CreateWindow(
		APP_NAME,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if(window == NULL) {
		error("SDL_CreateWindow Failed", SDL_GetError());
		goto error_window;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer == NULL) {
		error("SDL_CreateRenderer Failed", SDL_GetError());
		goto error_renderer;
	}
	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGB888,
		SDL_TEXTUREACCESS_STATIC,
		WINDOW_WIDTH,
		WINDOW_HEIGHT);
	if(texture == NULL) {
		error("SDL_CreateTexture Failed", SDL_GetError());
		goto error_texture;
	}
	cCanvas = canvas_create(WINDOW_WIDTH, WINDOW_HEIGHT);
	if(cCanvas == NULL) {
		error("Allocation error", "canvas - init");
		goto error_canvas;
	}
	iconGrid = grid_create(
		ICON_GRID_POS_X,
		ICON_GRID_POS_Y,
		ICON_GRID_SIZE_X,
		ICON_GRID_SIZE_Y,
		ICON_GRID_CELL_SIZE,
		ICON_GRID_CELL_PAD,
		ICON_GRID_CELL_BORDER,
		icon_grid_on_click);
	if(iconGrid == NULL) {
		error("Allocation error", "grid - init");
		goto error_icon_grid;
	}
	cIcon = icon_create();
	if(cIcon == NULL) {
		error("Allocation error", "icon - init");
		goto error_icon;
	}
	iconData = (Uint8 *)calloc(8, sizeof(Uint8));
	if(iconData == NULL) {
		error("Allocation error", "icon data - init");
		goto error_icon_data;
	}
	clearButton = button_create(
		420, 5, clear_button_on_click, "CLEAR", 2, 10, 0xFFFFFF, 0x000000);
	if(clearButton == NULL) {
		error("Allocation error", "clear button - init");
		goto error_clear_button;
	}
	exitButton = button_create(
		420, 46, exit_button_on_click, "EXIT ", 2, 10, 0xFFFFFF, 0x000000);
	if(exitButton == NULL) {
		error("Allocation error", "exit button - init");
		goto error_exit_button;
	}
	return;
	// Error handling
error_exit_button:
	button_destroy(exitButton);
error_clear_button:
	free(iconData);
error_icon_data:
	icon_destroy(cIcon);
error_icon:
	grid_destroy(iconGrid);
error_icon_grid:
	canvas_destroy(cCanvas);
error_canvas:
	SDL_DestroyTexture(texture);
error_texture:
	SDL_DestroyRenderer(renderer);
error_renderer:
	SDL_DestroyWindow(window);
error_window:
	SDL_Quit();
	exit(1);
}

void
destroy()
{
	free(iconData);
	icon_destroy(cIcon);
	grid_destroy(iconGrid);
	canvas_destroy(cCanvas);
	button_destroy(clearButton);
	button_destroy(exitButton);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

#pragma mark DRAW

Uint32
get_font_idx(Uint32 n_byte, Uint32 y)
{
	Uint32 init_idx = 4 * n_byte;
	Uint32 r = 0;
	for(Uint32 idx = init_idx; idx < init_idx + 4; idx++) {
		if(grid_get(iconGrid, idx, y) == ON)
			r = (r | 0x01);
		if(idx != init_idx + 3)
			r = r << 1;
	}
	return r;
}

void
redraw_icon_values()
{
	Uint32 x;
	Uint32 y = (ICON_GRID_CELL_SIZE - (FONT_HEX64_HEIGHT * FONT_SCALE)) / 2 + 2;
	Uint32 n_byte;
	for(Uint32 line = 0; line < ICON_GRID_SIZE_Y; line++) {
		x = ICON_GRID_CELL_SIZE * ICON_GRID_SIZE_X +
			(2 * FONT_HEX64_KERNING * FONT_SCALE);
		for(Uint32 character = 0; character < 4; character++) {
			switch(character) {
			case 0:
				font_hex64_draw(cCanvas, x, y, 0, FONT_SCALE, 0x000000);
				break;
			case 1:
				font_hex64_draw(cCanvas, x, y, 16, FONT_SCALE, 0x000000);
				break;
			default:
				n_byte = (character == 2) ? 0 : 1;
				font_hex64_draw(
					cCanvas,
					x,
					y,
					get_font_idx(n_byte, line),
					FONT_SCALE,
					0x000000);
				break;
			}
			x += (FONT_HEX64_WIDTH + FONT_HEX64_KERNING) * FONT_SCALE;
		}
		y += ICON_GRID_CELL_SIZE;
	}
}

void
redraw()
{
	canvas_clear(cCanvas, 0xFFFFFF);

	grid_draw(iconGrid, cCanvas, 0x000000);
	redraw_icon_values();
	canvas_draw_rect(cCanvas, 9, 329, 65, 65, 0, FILL_NONE, 0x0000000);
	icon_draw(cIcon, cCanvas, 10, 330, 0, 8, 0xFFFFFF, 0x000000);
	canvas_draw_rect(cCanvas, 83, 329, 33, 33, 0, FILL_NONE, 0x0000000);
	icon_draw(cIcon, cCanvas, 84, 330, 0, 4, 0xFFFFFF, 0x000000);
	canvas_draw_rect(cCanvas, 125, 329, 17, 17, 0, FILL_NONE, 0x0000000);
	icon_draw(cIcon, cCanvas, 126, 330, 0, 2, 0xFFFFFF, 0x000000);
	canvas_draw_rect(cCanvas, 151, 329, 9, 9, 0, FILL_NONE, 0x0000000);
	icon_draw(cIcon, cCanvas, 152, 330, 0, 1, 0xFFFFFF, 0x000000);

	button_draw(clearButton, cCanvas);
	button_draw(exitButton, cCanvas);

	canvas_draw_rect(cCanvas, 420, 87, 100, 232, 0, FILL_FILLED, 0x000000);

	canvas_update_texture(cCanvas, texture);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

#pragma mark UTILS

void
update_icon()
{
	memset(iconData, 0x00, 8 * sizeof(Uint8));
	for(Uint8 y = 0; y < 8; y++)
		for(Uint8 x = 0; x < 8; x++)
			iconData[y] =
				(iconData[y] | (grid_get(iconGrid, x, y) == ON ? 0x01 : 0x00))
				<< (x == 7 ? 0 : 1);
	memcpy(cIcon->data, iconData, 8 * sizeof(Uint8));
}

#pragma mark SDL

void
on_mouse_event(SDL_Event *evt)
{
	switch(evt->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONUP: break;
	case SDL_MOUSEBUTTONDOWN:
		grid_process_event(iconGrid, evt);
		button_process_event(clearButton, evt);
		button_process_event(exitButton, evt);
		break;
	}
}

#pragma mark MAIN PROGRAM

int
main()
{
	int tick_next = 0;
	SDL_Event event;
	init_app();
	update_icon();
	redraw();
	while(1) {
		int tick = SDL_GetTicks();
		if(tick < tick_next)
			SDL_Delay(tick_next - tick);
		tick_next = tick + (1000 / FPS);
		update_icon();
		redraw();
		while(SDL_PollEvent(&event) != 0) {
			switch(event.type) {
			case SDL_QUIT: destroy(); return 0;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEMOTION: on_mouse_event(&event); break;
			}
		}
	}
}
