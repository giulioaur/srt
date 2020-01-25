#pragma once

#include "paths.h"

/*********************** DEFINE ***********************/

#ifdef _WIN32
#define INLINE inline
#else
#define INLINE inline
#endif // _WIN32


/*********************** TYPES ***********************/

typedef size_t umsize;

/*********************** FUNCTIONS ***********************/

namespace srt
{

/**
 * Just a wrapper around the std::swap that enables the ADL.
 *
 * @param a The first element to swap.
 * @param b The second element to swap.
 */
template <class T>
INLINE void swap(T& a, T& b)
{
    using std::swap;
    swap(a, b);
}

}