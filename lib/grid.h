#include "canvas.h"
#include "color.h"
#include "error.h"
#include <SDL.h>
#include <string.h>

#ifndef __GRID_H
#define __GRID_H

typedef enum { OFF = 0, ON = 1 } grid_cell_state;
typedef enum {
	POINT_NOT_IN_CELL = 0,
	POINT_IN_CELL = 1
} grid_point_in_cell_result;

typedef struct _grid grid;

typedef void (*grid_on_click)(grid *g, Uint32 x, Uint32 y);

struct _grid {
	Uint32 POS_X;
	Uint32 POS_Y;
	Uint32 N_CELLS_X;
	Uint32 N_CELLS_Y;
	Uint32 CELL_SIZE;
	Uint32 CELL_PAD;
	Uint32 CELL_BORDER;
	grid_cell_state *data;
	grid_on_click on_click;
};

#pragma mark MEMORY

grid *
grid_create(
	Uint32 pos_x,
	Uint32 pos_y,
	Uint32 size_x,
	Uint32 size_y,
	Uint32 cell_size,
	Uint32 cell_pad,
	Uint32 cell_border,
	grid_on_click on_click)
{
	grid *g = (grid *)calloc(1, sizeof(grid));
	if(g == NULL) {
		error("Allocating", "grid");
		return NULL;
	}
	grid_cell_state *d =
		(grid_cell_state *)calloc(size_x * size_y, sizeof(grid_cell_state));
	if(d == NULL) {
		error("Allocating", "grid data");
		free(g);
		return NULL;
	}
	g->POS_X = pos_x;
	g->POS_Y = pos_y;
	g->N_CELLS_X = size_x;
	g->N_CELLS_Y = size_y;
	g->CELL_SIZE = cell_size;
	g->CELL_PAD = cell_pad;
	g->CELL_BORDER = cell_border;
	g->data = d;
	g->on_click = on_click;
	return g;
}

void
grid_destroy(grid *g)
{
	free(g->data);
	free(g);
}

#pragma mark UTILS

unsigned int
grid_idx(grid *g, Uint32 x, Uint32 y)
{
	return x + (y * g->N_CELLS_X);
}

grid_cell_state
grid_get(grid *g, Uint32 x, Uint32 y)
{
	return g->data[grid_idx(g, x, y)];
}

void
grid_set(grid *g, Uint32 x, Uint32 y, grid_cell_state state)
{
	g->data[grid_idx(g, x, y)] = state;
}

void
grid_switch(grid *g, Uint32 x, Uint32 y)
{
	if(g->data[grid_idx(g, x, y)] == ON)
		g->data[grid_idx(g, x, y)] = OFF;
	else
		g->data[grid_idx(g, x, y)] = ON;
}

void
grid_reset(grid *g, grid_cell_state state)
{
	memset(
		g->data, state, g->N_CELLS_X * g->N_CELLS_Y * sizeof(grid_cell_state));
}

void
grid_draw(grid *g, canvas *c, color grid_color)
{
	for(Uint32 cy = 0; cy < g->N_CELLS_Y; cy++)
		for(Uint32 cx = 0; cx < g->N_CELLS_X; cx++) {
			fill_style fill =
				g->data[grid_idx(g, cx, cy)] == ON ? FILL_FILLED : FILL_NONE;
			Uint32 wh = g->CELL_SIZE - g->CELL_PAD;
			canvas_draw_rect(
				c,
				(cx * g->CELL_SIZE) + g->POS_X + g->CELL_PAD,
				(cy * g->CELL_SIZE) + g->POS_Y + g->CELL_PAD,
				wh,
				wh,
				g->CELL_BORDER,
				fill,
				grid_color);
		}
}

grid_point_in_cell_result
grid_point_in_cell(grid *g, Uint32 x, Uint32 y, Uint32 cx, Uint32 cy)
{
	if(point_in_rectangle(
		   x,
		   y,
		   (cx * g->CELL_SIZE) + g->CELL_PAD,
		   (cy * g->CELL_SIZE) + g->CELL_PAD,
		   g->CELL_SIZE - g->CELL_PAD,
		   g->CELL_SIZE - g->CELL_PAD))
		return POINT_IN_CELL;
	return POINT_NOT_IN_CELL;
}

void
grid_process_event(grid *g, SDL_Event *evt)
{
	switch(evt->type) {
	case SDL_MOUSEBUTTONDOWN:
		for(int y = 0; y < g->N_CELLS_Y; y++)
			for(int x = 0; x < g->N_CELLS_X; x++)
				if(grid_point_in_cell(g, evt->button.x, evt->button.y, x, y))
					g->on_click(g, x, y);
		break;
	}
}

#endif