/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  STOPWATCH CLASS FILE	                           *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "utility/Stopwatch.hpp"

namespace srt::utility {

Stopwatch::Stopwatch(){
	timeStart = std::chrono::high_resolution_clock::now();
}
	
void Stopwatch::start() {
	this->timeStart = std::chrono::high_resolution_clock::now();
}

double Stopwatch::end() const{
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - this->timeStart;
	return time.count();
}

long Stopwatch::endms() const{
	auto time = std::chrono::high_resolution_clock::now() - this->timeStart;
	return std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
}

}

