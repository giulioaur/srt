/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  STOPWATCH CLASS FILE	                           *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Stopwatch.hpp"

using namespace std::chrono;

namespace srt {
namespace utility {
	Stopwatch::Stopwatch(){
		timeStart = high_resolution_clock::now();
	}
	
	void Stopwatch::start() {
		this->timeStart = high_resolution_clock::now();
	}

	double Stopwatch::end() const{
		duration<double> time = high_resolution_clock::now() - this->timeStart;
		return time.count();
	}

	long Stopwatch::endms() const{
		auto time = high_resolution_clock::now() - this->timeStart;
		return duration_cast<milliseconds>(time).count();
	}
}
}

