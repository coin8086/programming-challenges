/***********************************************************
 * Author: Robert Zhang(louirobert@gmail.com)
 * This program is distributed under GNU GPL.
 **********************************************************/

#ifndef __DEBUG_HELPER_H__
#define __DEBUG_HELPER_H__

#ifdef DEBUG
#include <stdio.h>
#define DEBUG_OUT(...) do {\
    fprintf(stderr, __VA_ARGS__); \
  } while(0);
#else
#define DEBUG_OUT(...)
#endif

#endif
