#include "error.h"
#include <SDL.h>

#ifndef __COLLISIONS_H
#define __COLLISIONS_H

typedef enum {
	COLLISION_NONE = 0,
	COLLISION_PARTIAL = 1,
	COLLISION_TOTAL = 2,
} collision_status;

#pragma mark UTILS

collision_status
point_in_rectangle(int px, int py, int rx, int ry, int rw, int rh)
{
	if((px > rx) && (px < rx + rw) && (py > ry) && (py < ry + rh))
		return COLLISION_TOTAL;
	return COLLISION_NONE;
}

#endif