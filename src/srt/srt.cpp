/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  GLOBAL INCLUDE                                     *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "srt.h"

float rand_float()
{
#ifdef _WIN32
    return rand() / (RAND_MAX + 1.0);
#elif
    return drand48()
#endif
}