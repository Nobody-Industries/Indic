#include "canvas.h"
#include "color.h"
#include <SDL.h>

#ifndef __FONTS_H
#define __FONTS_H

#define FONT_HEX64_WIDTH 4
#define FONT_HEX64_HEIGHT 6
#define FONT_HEX64_KERNING 1

#define FONT_64_WIDTH 8
#define FONT_64_HEIGHT 8
#define FONT_64_LINE_HEIGHT 10

typedef enum { FONT_HEX_64, FONT_64 } SYSTEM_FONTS;

Uint8 font_hex64[17][3] = {
	{0x69, 0x99, 0x96}, /* 0 */
	{0x62, 0x22, 0x22}, /* 1 */
	{0x69, 0x16, 0x8F}, /* 2 */
	{0xE1, 0x1E, 0x1E}, /* 3 */
	{0x99, 0x97, 0x11}, /* 4 */
	{0xF8, 0x8E, 0x1E}, /* 5 */
	{0x69, 0x8E, 0x96}, /* 6 */
	{0xE1, 0x17, 0x11}, /* 7 */
	{0x69, 0x96, 0x96}, /* 8 */
	{0x69, 0x97, 0x11}, /* 9 */
	{0x69, 0x9F, 0x99}, /* A */
	{0xE9, 0xE9, 0x9E}, /* B */
	{0x78, 0x88, 0x87}, /* C */
	{0xE9, 0x99, 0x9E}, /* D */
	{0xF8, 0x8E, 0x8F}, /* E */
	{0x78, 0x8E, 0x88}, /* F */
	{0x09, 0x96, 0x99}, /* x */
};

void
font_hex64_draw(
	canvas *c, Uint32 x, Uint32 y, Uint32 idx, Uint32 scale, color font_color)
{
	Uint32 d, v, dx = x, dy = y;
	for(Uint32 cy = 0; cy < 6; cy++, dy += scale) {
		for(Uint32 cx = 0; cx < 4; cx++, dx += scale) {
			d = (7 - ((cy % 2) * 4)) - cx;
			v = ((font_hex64[idx][cy / 2]) >> d) & 0x01;
			if(v == 0x01)
				canvas_draw_rect(
					c, dx, dy, scale, scale, 1, FILL_FILLED, font_color);
		}
		dx = x;
	}
}

Uint8 font_64[56][8] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* [SPACE] */

	{0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66}, /* A */
	{0x7C, 0x7E, 0x66, 0x7C, 0x7E, 0x66, 0x7E, 0x7C}, /* B */
	{0x3C, 0x7E, 0x66, 0x60, 0x60, 0x66, 0x7E, 0x3C}, /* C */
	{0x7C, 0x7E, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x7C}, /* D */
	{0x7E, 0x7E, 0x60, 0x78, 0x78, 0x60, 0x7E, 0x7E}, /* E */
	{0x7E, 0x7E, 0x60, 0x78, 0x78, 0x60, 0x60, 0x60}, /* F */
	{0x3E, 0x7E, 0x60, 0x6E, 0x6E, 0x66, 0x7E, 0x3E}, /* G */
	{0x66, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66}, /* H */
	{0x3C, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x3C}, /* I */
	{0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x7E, 0x3C}, /* J */
	{0x66, 0x6E, 0x7C, 0x78, 0x78, 0x7C, 0x6E, 0x66}, /* K */
	{0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x7E}, /* L */
	{0x66, 0x7E, 0x5A, 0x5A, 0x42, 0x42, 0x66, 0x66}, /* M */
	{0x66, 0x76, 0x7E, 0x7E, 0x6E, 0x66, 0x66, 0x66}, /* N */
	{0x3C, 0x7E, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x3C}, /* O */
	{0x3C, 0x7E, 0x66, 0x7E, 0x7C, 0x60, 0x60, 0x60}, /* P */
	{0x3C, 0x7E, 0x66, 0x66, 0x6E, 0x6E, 0x7E, 0x3E}, /* Q */
	{0x3C, 0x7E, 0x66, 0x66, 0x7C, 0x7E, 0x66, 0x66}, /* R */
	{0x3E, 0x7E, 0x60, 0x7C, 0x3E, 0x06, 0x7E, 0x7C}, /* S */
	{0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, /* T */
	{0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x3C}, /* U */
	{0x66, 0x66, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x18}, /* V */
	{0x66, 0x66, 0x42, 0x5A, 0x4A, 0x6E, 0x7E, 0x3C}, /* W */
	{0x66, 0x66, 0x66, 0x24, 0x18, 0x24, 0x66, 0x66}, /* X */
	{0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18}, /* Y */
	{0x7E, 0x7E, 0x0E, 0x1C, 0x38, 0x70, 0x7E, 0x7E}, /* Z */

	{0x3C, 0x7E, 0x66, 0x6E, 0x76, 0x66, 0x7E, 0x3C}, /* O */
	{0x3C, 0x3C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C}, /* 1 */
	{0x7C, 0x7E, 0x0E, 0x1C, 0x38, 0x70, 0x7E, 0x7E}, /* 2 */
	{0x7C, 0x7E, 0x06, 0x7E, 0x7E, 0x06, 0x7E, 0x7C}, /* 3 */
	{0x66, 0x66, 0x66, 0x7E, 0x3E, 0x06, 0x06, 0x06}, /* 4 */
	{0x7E, 0x7E, 0x60, 0x7C, 0x7E, 0x06, 0x7E, 0x7C}, /* 5 */
	{0x3C, 0x7E, 0x60, 0x7C, 0x7E, 0x66, 0x7E, 0x3C}, /* 6 */
	{0x7E, 0x7E, 0x06, 0x1E, 0x1E, 0x06, 0x06, 0x06}, /* 7 */
	{0x3C, 0x7E, 0x66, 0x3C, 0x7E, 0x66, 0x7E, 0x3C}, /* 8 */
	{0x3C, 0x7E, 0x66, 0x7E, 0x3E, 0x06, 0x06, 0x06}, /* 9 */

	{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18}, /* ! */
	{0x36, 0x36, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00}, /* " */
	{0x24, 0x7E, 0x7E, 0x24, 0x24, 0x7E, 0x7E, 0x24}, /* # */
	{0x00, 0x66, 0x6E, 0x1C, 0x38, 0x76, 0x66, 0x00}, /* % */
	{0x0C, 0x3E, 0x6C, 0x7E, 0x6C, 0x7E, 0x3E, 0x0C}, /* & */
	{0x1C, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x1C}, /* ( */
	{0x38, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x38}, /* ) */
	{0x00, 0x18, 0x18, 0x7E, 0x7E, 0x18, 0x18, 0x00}, /* + */
	{0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x08, 0x10}, /* , */
	{0x00, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x00}, /* - */
	{0x00, 0x06, 0x0E, 0x1C, 0x38, 0x70, 0x60, 0x00}, /* / */
	{0x7C, 0x7E, 0x06, 0x3E, 0x3C, 0x30, 0x00, 0x30}, /* ? */
	{0x00, 0x60, 0x70, 0x38, 0x1C, 0x0E, 0x06, 0x00}, /* \ */
	{0x3C, 0x7E, 0x6A, 0x6A, 0x6E, 0x60, 0x7E, 0x3C}, /* @ */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E}, /* _ */
	{0x00, 0x60, 0x38, 0x0E, 0x0E, 0x38, 0x60, 0x00}, /* > */
	{0x00, 0x7E, 0x7E, 0x00, 0x00, 0x7E, 0x7E, 0x00}, /* = */
	{0x00, 0x06, 0x1C, 0x70, 0x70, 0x1C, 0x06, 0x00}, /* < */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18}, /* . */

};

void
font_64_draw(
	canvas *c, Uint32 x, Uint32 y, Uint32 idx, Uint32 scale, color font_color)
{
	Uint32 dx = x, dy = y;
	Uint8 v;
	for(Uint32 y = 0; y < FONT_64_HEIGHT; y++, dy += scale) {
		for(Uint32 x = 0; x < FONT_64_WIDTH; x++, dx += scale) {
			v = (font_64[idx][y] >> (7 - x)) & 0x01;
			if(v == 0x01)
				canvas_draw_rect(
					c, dx, dy, scale, scale, 0, FILL_FILLED, font_color);
		}
		dx = x;
	}
}

Uint32
font_64_char_to_idx(const char c)
{
	/* SPACE */
	if(c == 32)
		return 0;
	/* ALPHABETIC CHARS (CAPS): 65..90 -> 1..26 */
	else if(c >= 65 && c <= 90)
		return c - 64;
	/* ALPHABETIC CHARS (SMALLS): 97..122 -> 1..26 */
	else if(c >= 97 && c <= 122)
		return c - 96;
	/* NUMBERS: 48..57 ->  27..36 */
	else if(c >= 48 && c <= 57)
		return c - 21;
	/* SPECIAL CHARS */
	else {
		switch(c) {
		case '!': return 37;
		case '"': return 38;
		case '#': return 39;
		case '%': return 40;
		case '&': return 41;
		case '(': return 42;
		case ')': return 43;
		case '+': return 44;
		case ',': return 45;
		case '-': return 46;
		case '/': return 47;
		case '?': return 48;
		case '\\': return 49;
		case '@': return 50;
		case '_': return 51;
		case '>': return 52;
		case '=': return 53;
		case '<': return 54;
		case '.': return 55;
		default: return 0;
		}
	}
}

void
font_64_write_string(
	canvas *c,
	const char *s,
	Uint32 x,
	Uint32 y,
	Uint32 scale,
	color font_color)
{
	const char *cs = s;
	Uint32 cx = x;
	Uint32 cy = y;
	while(*cs != '\0') {
		if(*cs == '\n') {
			cy += (FONT_64_LINE_HEIGHT * scale);
			cx = x;
		} else {
			font_64_draw(
				c, cx, cy, font_64_char_to_idx(*cs), scale, font_color);
			cx += (FONT_64_WIDTH * scale);
		}
		cs++;
	}
	return;
}

#endif