#include "canvas.h"
#include "error.h"
#include <SDL.h>

#ifndef __ICON_H
#define __ICON_H

#define ICON_SIZE 8

typedef struct {

	Uint8 *data;

} icon;

#pragma mark MEMORY

icon *
icon_create()
{
	icon *i = (icon *)calloc(1, sizeof(icon));
	if(i == NULL) {
		error("Allocating", "icon");
		return NULL;
	}
	Uint8 *d = (Uint8 *)calloc(ICON_SIZE, sizeof(Uint8));
	if(i == NULL) {
		free(i);
		error("Allocating", "icon data");
		return NULL;
	}
	i->data = d;
	return i;
}

void
icon_destroy(icon *i)
{
	free(i->data);
	free(i);
}

#pragma mark UTILS

void
icon_draw(
	icon *i,
	canvas *c,
	Uint32 x,
	Uint32 y,
	Uint32 pad,
	Uint32 scale,
	color color_bg,
	color color_fg)
{
	int v, h, cx, cy;
	Uint8 is_on;
	for(v = 0; v < 8; v++)
		for(h = 0; h < 8; h++) {
			is_on = (i->data[v] >> (7 - h)) & 0x01;
			cx = x + pad + (h * scale);
			cy = y + pad + (v * scale);
			for(int ny = 0; ny < scale; ny++)
				for(int nx = 0; nx < scale; nx++)
					canvas_pixel_set(
						c, cx + nx, cy + ny, is_on ? color_fg : color_bg);
		}
}

#endif