#ifndef ERRORFN_H
#define ERRORFN_H

#include <stdlib.h>
#include <stdio.h>

static inline void handle_error(const char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

#endif