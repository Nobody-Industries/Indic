#include "canvas.h"
#include "fonts.h"
#include "color.h"
#include "collisions.h"
#include <string.h>
#include <SDL.h>

#ifndef __BUTTON_H
#define __BUTTON_H

typedef struct _button button;

typedef void (*button_on_click)(button *b, Uint32 x, Uint32 y);

typedef struct _button {
	Uint32 x, y;
	button_on_click callback;
	char *text;
	Uint32 scale;
	Uint32 padding;
	color fgColor;
	color bgColor;
} button;

#pragma mark MEMORY

button *
button_create(
	Uint32 x,
	Uint32 y,
	button_on_click callback,
	const char *text,
	Uint32 scale,
	Uint32 padding,
	color fgColor,
	color bgColor)
{
	button *b = (button *)calloc(1, sizeof(button));
	if(b == NULL)
		return NULL;
	b->text = (char *)calloc(strlen(text), sizeof(char));
	if(b->text == NULL) {
		free(b);
		return NULL;
	}
	strcpy(b->text, text);
	b->x = x;
	b->y = y;
	b->callback = callback;
	b->scale = scale;
	b->padding = padding;
	b->fgColor = fgColor;
	b->bgColor = bgColor;
	return b;
}

void
button_destroy(button *b)
{
	free(b->text);
	free(b);
}

#pragma mark UTILS

void
button_draw(button *b, canvas *c)
{
	canvas_draw_rect(
		c,
		b->x,
		b->y,
		(strlen(b->text) * FONT_64_WIDTH * b->scale) + (2 * b->padding),
		(FONT_64_HEIGHT * b->scale) + (2 * b->padding),
		b->scale,
		FILL_FILLED,
		b->bgColor);
	font_64_write_string(
		c, b->text, b->x + b->padding, b->y + b->padding, b->scale, b->fgColor);
}

void
button_check_click(button *b, Uint32 x, Uint32 y)
{
	if(point_in_rectangle(
		   x,
		   y,
		   b->x,
		   b->y,
		   (strlen(b->text) * FONT_64_WIDTH * b->scale) + (2 * b->padding),
		   (FONT_64_HEIGHT * b->scale) + (2 * b->padding)))
		b->callback(b, x, y);
}

void
button_process_event(button *b, SDL_Event *evt)
{
	switch(evt->type) {
	case SDL_MOUSEBUTTONDOWN:
		button_check_click(b, evt->button.x, evt->button.y);
		break;
	}
}

#endif
