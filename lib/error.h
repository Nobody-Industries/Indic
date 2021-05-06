#include <stdio.h>

#ifndef __ERROR_H
#define __ERROR_H

#pragma mark UTILS

void
error(const char *msg, const char *err)
{
	printf("ERROR: %s [%s]", msg, err);
}

#endif