#pragma once

#include "paths.h"

#include <limits>

/*********************** DEFINE ***********************/

#ifdef _WIN32
#define INLINE inline
#else
#define INLINE inline
#endif // _WIN32

#define M_PI 3.1415926535897

#define FLOAT_MAX std::numeric_limits<float>::max()


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

template <class ITERATOR, class FUNCTOR >
INLINE void map(ITERATOR start, ITERATOR end, const FUNCTOR& func)
{
	while (start < end)
	{
		func(*start);
		++start;
	}
}

}