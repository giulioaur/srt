/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  STOPWATCH CLASS HEADER                             *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#pragma once

// System library includes.
#include <chrono>

namespace srt::utility 
{

/*
 * It is just a stopwatch to keep time for performance's purposes.
 */ 
class Stopwatch
{
public:

	Stopwatch();
	void start();
	double end() const;
	long endms() const;

private:

	std::chrono::high_resolution_clock::time_point timeStart;
};

} 
