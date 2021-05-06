#include "collisions.h"
#include "color.h"
#include "error.h"
#include <SDL.h>

#ifndef __CANVAS_H
#define __CANVAS_H

typedef struct {
	Uint32 WIDTH;
	Uint32 HEIGHT;
	Uint32 *pixels;
} canvas;

typedef enum {
	FILL_NONE = 0,
	FILL_FILLED = 1,
} fill_style;

#pragma mark MEMORY

canvas *
canvas_create(Uint32 width, Uint32 height)
{
	canvas *c = (canvas *)calloc(1, sizeof(canvas));
	if(c == NULL) {
		error("Allocating", "canvas");
		return NULL;
	}
	Uint32 *p = (Uint32 *)calloc(width * height, sizeof(Uint32));
	if(p == NULL) {
		error("Allocating", "canvas pixels");
		free(c);
		return NULL;
	}
	c->HEIGHT = height;
	c->WIDTH = width;
	c->pixels = p;
	return c;
}

void
canvas_destroy(canvas *c)
{
	free(c->pixels);
	free(c);
}

#pragma mark UTILS

Uint32
canvas_idx(canvas *c, Uint32 x, Uint32 y)
{
	return x + (y * c->WIDTH);
}

void
canvas_pixel_set(canvas *c, int x, int y, color pixel_color)
{
	if(x >= 0 && x < c->WIDTH && y >= 0 && y < c->HEIGHT)
		c->pixels[canvas_idx(c, x, y)] = pixel_color;
}

Uint32
canvas_pixel_get(canvas *c, int x, int y)
{
	if(x >= 0 && x < c->WIDTH && y >= 0 && y < c->HEIGHT)
		return c->pixels[canvas_idx(c, x, y)];
	return 0x000000;
}

void
canvas_draw_rect(
	canvas *c,
	Uint32 x,
	Uint32 y,
	Uint32 w,
	Uint32 h,
	Uint32 border_size,
	fill_style fill,
	color rect_color)
{
	// Inner rectangle
	Uint32 rx = x + border_size;
	Uint32 ry = y + border_size;
	Uint32 rw = w - (2 * border_size);
	Uint32 rh = h - (2 * border_size);
	for(Uint32 cy = y; cy <= y + h; cy++)
		for(Uint32 cx = x; cx <= x + w; cx++)
			if(fill == FILL_FILLED ||
			   (fill == FILL_NONE &&
				(point_in_rectangle(cx, cy, rx, ry, rw, rh) == COLLISION_NONE)))
				canvas_pixel_set(c, cx, cy, rect_color);
}

void
canvas_update_texture(canvas *c, SDL_Texture *texture)
{
	SDL_UpdateTexture(texture, NULL, c->pixels, c->WIDTH * sizeof(Uint32));
}

void
canvas_clear(canvas *c, color clear_color)
{
	memset(c->pixels, clear_color, c->WIDTH * c->HEIGHT * sizeof(Uint32));
}

#endif