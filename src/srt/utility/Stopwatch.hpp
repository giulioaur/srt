/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  STOPWATCH CLASS HEADER                             *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_UTILITY_STOPWATCH_S
#define S_UTILITY_STOPWATCH_S

// System library includes.
#include <chrono>

namespace srt { 
namespace utility {

// It is just a stopwatch to keep time for performance's purposes.
class Stopwatch{
	std::chrono::high_resolution_clock::time_point timeStart;
public:
	Stopwatch();
	void start();
	double end() const;
	long endms() const;
};
} 
}

#endif